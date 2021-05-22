//
// Created by Gerry on 2021-04-17.
//
#include <threading/Lock.h>
namespace threading {
    KeySession Lock::use() {
        return std::unique_lock<std::mutex>{mtx};
    }

    void Lock::wait(KeySession &key) {
        condLock.wait(key);
    }

    void Lock::notify() {
        condLock.notify_one();
    }

    void Lock::notifyAll() {
        condLock.notify_all();
    }
}