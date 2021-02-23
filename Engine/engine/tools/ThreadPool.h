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
using ThreadFunc = void(*)(In&);

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
        poolKey = dataLock.createKey();
        for(int i = 0; i < size; i++) {
            threads.push_back(std::thread([&]() {
                this->threadRunning();
            }));
        }
    }

    void threadRunning() {
        Scope<LockKey> key = dataLock.createKey();
        while(isRunning) {
            printf("wowow\n");

            key->lock();
            while(data.empty()) {
                key->wait();
            }
            data.pop_back();

            printf("wowow after\n");
            key->unlock();


        }
    }

    ~ThreadPool() {
        isRunning = false;
    }

    void enqueue(ThreadFunc<In> func, In& value) {
        poolKey->lock();
        data.push_back({value, func});
        poolKey->notify();
        poolKey->unlock();
    }
private:
    std::vector<std::thread> threads;
    std::vector<ThreadData<In>> data;
    Scope<LockKey> poolKey;
    VoxEng::Lock dataLock;
    bool isRunning = true;
};


#endif //CPPMC_THREADPOOL_H
