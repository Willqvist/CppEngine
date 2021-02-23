//
// Created by Gerry on 2021-02-23.
//

#ifndef CPPMC_LOCK_H
#define CPPMC_LOCK_H
#include <mutex>
#include "core/Core.h"
namespace VoxEng {
    struct LockKey {
    public:
        LockKey(std::mutex &lock, std::condition_variable& condLock) : mtx(lock), condLock(condLock) {
        }

        void lock() {
            _lock = std::unique_lock<std::mutex>{mtx};
        }

        void wait() {
            condLock.wait(_lock);
        }

        void notify() {
            condLock.notify_one();
        }

        void notifyAll() {
            condLock.notify_all();
        }

        void unlock() {
            _lock.unlock();
        }

    private:
        std::unique_lock<std::mutex> _lock;
        std::mutex& mtx;
        std::condition_variable& condLock;
    };

    class Lock {
    public:
        Scope<LockKey> createKey() {
            Scope<LockKey> key = CreateScope<LockKey>(_lock,condLock);
            return std::move(key);
        }

    private:
        std::mutex _lock;
        std::condition_variable condLock;
    };
}


#endif //CPPMC_LOCK_H
