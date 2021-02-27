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
struct ThreadData {
    In value;
    ThreadFunc<In> callback;
};
using namespace VoxEng;
template<class In>
class ThreadPool {
public:
    ThreadPool(int size) {
        for(int i = 0; i < size; i++) {
            int id = i;
            threads.push_back(std::thread([this,id]() {
                this->threadRunning(id);
            }));
        }
    }

    void threadRunning(int id) {
        try {
            while (isRunning) {
                ThreadData<In> tData;
                {
                    KeyLock key = dataLock.lock();
                    while (data.empty()) {
                        dataLock.wait(key);
                    }
                    tData = data.back();
                    data.pop_back();
                }
                tData.callback(tData.value, id);
            }
        }
        catch (const std::exception e) {
            printf("err: %s \n", e.what());
        }
    }

    ~ThreadPool() {
        isRunning = false;
    }

    void enqueue(ThreadFunc<In> func, In& value) {
        {
            KeyLock key = dataLock.lock();
            data.push_back({ value, func });
        }
        dataLock.notify();
    }
private:
    std::vector<std::thread> threads;
    std::vector<ThreadData<In>> data;
    Lock dataLock;
    bool isRunning = true;
};


#endif //CPPMC_THREADPOOL_H
