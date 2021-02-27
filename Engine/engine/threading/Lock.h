//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_LOCK_H
#define CPPMC_LOCK_H
#include <mutex>
#include <functional>
#include "core/Core.h"
#include "core/KeyCode.h"
using ThreadCallback = std::function<void(void*)>;

namespace VoxEng {
    using KeyLock =  std::unique_lock<std::mutex>;
    class Lock {
    public:
    	
    	/*
        Scope<LockKey> createKey() {
            Scope<LockKey> key = CreateScope<LockKey>(_lock,condLock);
            return std::move(key);
        }
        */

        KeyLock lock() {
            return std::unique_lock<std::mutex> {mtx};
        }

        void wait(KeyLock& key) {
            condLock.wait(key);
        }

        void notify() {
            condLock.notify_one();
        }

        void notifyAll() {
            condLock.notify_all();
        }

    private:
        std::mutex mtx;
        std::condition_variable condLock;
    };
}


#endif //CPPMC_LOCK_H
