//
// Created by Gerry on 2021-02-24.
//

#ifndef CPPMC_MAINTHREAD_H
#define CPPMC_MAINTHREAD_H

#include "Lock.h"
#include <queue>
#include <utility>

struct MainThreadData {
    void* data;
    ThreadCallback callback;
};

namespace VoxEng {
    class MainThread {
    public: 	
        static void enqueue(void* data, ThreadCallback callback);

        static void callIfExists(int maxMs);
    private:
        static std::queue<MainThreadData> callbacks;
        static Lock lock;
    };
}


#endif //CPPMC_MAINTHREAD_H
