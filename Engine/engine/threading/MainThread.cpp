//
// Created by Gerry on 2021-02-24.
//

#include "MainThread.h"
#include <tools/Tools.h>

void VoxEng::MainThread::enqueue(void *data, ThreadCallback callback) {
    KeyLock key = lock.lock();
    callbacks.push({data, std::move(callback)});
}

void VoxEng::MainThread::callIfExists(int maxMs) {
    KeyLock key = lock.lock();
    int accumTim = 0;
    while(!callbacks.empty())
    {
        auto start = getTime();
        printf("HERE! \n");
        const MainThreadData& data = callbacks.front();
        data.callback(data.data);
        callbacks.pop();
        auto end = getTime();
        accumTim += end-start;
        if(accumTim >= maxMs)
            break;
    }
}

VoxEng::Lock VoxEng::MainThread::lock;
std::queue<MainThreadData> VoxEng::MainThread::callbacks;

