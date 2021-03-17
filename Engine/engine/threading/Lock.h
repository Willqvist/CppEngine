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
        KeyLock lock();
        void wait(KeyLock& key);
        void notify();
        void notifyAll();

    private:
        std::mutex mtx;
        std::condition_variable condLock;
    };
}


#endif //CPPMC_LOCK_H
