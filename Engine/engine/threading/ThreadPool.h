//
// Created by Gerry on 2020-12-03.
//

#ifndef CPPMC_THREADPOOL_H
#define CPPMC_THREADPOOL_H
#include<thread>
#include <vector>
#include <mutex>
#include <threading/Lock.h>
template<class In>
using ThreadFunc = std::function<void(In&, int threadId)>;

template<class In>
using ThreadSelectFunc = std::function<int(In&)>;
template<class In>
struct ThreadData {
    In value;
    ThreadFunc<In> callback;
};

namespace VoxEng {
    template<class In>
    class ThreadPool {
    public:
        ThreadPool(int size) {
            freezes = new bool[size];
            for (int i = 0; i < size; i++) {
                int id = i;
                freezes[i] = false;
                threads.push_back(std::thread([this, id]() {
                    this->threadRunning(id);
                }));
            }
        }

        void select(const ThreadSelectFunc<In> &func) {
            this->selectFunc = func;
        }

        void threadRunning(int id) {
            try {
                while (isRunning) {
                    ThreadData<In> tData;
                    {
                        KeyLock key = dataLock.lock();
                        printf("id: %d\n", id);
                        while (data.empty() || freezes[id]) {
                            dataLock.wait(key);
                        }
                        if (selectFunc == nullptr) {
                            tData = data.back();
                            data.pop_back();
                        } else {

                            int max = INT_MAX;
                            int index = 0;
                            int i = 0;
                            for (auto val : data) {
                                int cMax = selectFunc(val.value);
                                if (cMax < max) {
                                    index = i;
                                    max = cMax;
                                }
                                i++;
                            }
                            tData = data[index];
                            data.erase(data.begin() + index);
                        }
                    }
                    tData.callback(tData.value, id);
                }
            }
            catch (const std::exception e) {
                printf("err: %s \n", e.what());
            }
        }

        void freeze(int threadId) {
            freezes[threadId] = true;
        }

        void unfreeze(int threadId) {
            freezes[threadId] = false;
            dataLock.notifyAll();
        }

        void enqueue(ThreadFunc<In> func, In &value) {
            {
                KeyLock key = dataLock.lock();
                data.push_back({value, func});
            }
            dataLock.notify();
        }

        ~ThreadPool() {
            isRunning = false;
            delete[] freezes;
        }


    private:
        std::vector<std::thread> threads;
        bool *freezes;
        std::vector<ThreadData<In>> data;
        Lock dataLock;
        ThreadSelectFunc<In> selectFunc = nullptr;
        bool isRunning = true;
    };
}


#endif //CPPMC_THREADPOOL_H
