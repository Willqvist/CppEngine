//
// Created by Gerry on 2021-03-16.
//
#include "Lock.h"

VoxEng::KeyLock VoxEng::Lock::lock() {
    return std::unique_lock<std::mutex> {mtx};
}

void VoxEng::Lock::wait(VoxEng::KeyLock &key) {
    condLock.wait(key);
}

void VoxEng::Lock::notify() {
    condLock.notify_one();
}

void VoxEng::Lock::notifyAll() {
    condLock.notify_all();
}