//
// Created by Gerry on 2021-02-24.
//

#ifndef CPPMC_MAINTHREAD_H
#define CPPMC_MAINTHREAD_H

#include "Lock.h"
#include <queue>
#include <utility>
#include <tools/Tools.h>

struct MainThreadData {
    void* data;
    ThreadCallback callback;
};
namespace VoxEng {
    class MainThread {
    public: 	
        static void enqueue(void* data, ThreadCallback callback) {
            KeyLock key = lock.lock();
            callbacks.push({data, std::move(callback)});
        }

        static void callIfExists(int maxMs) {
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
    private:
        static inline std::queue<MainThreadData> callbacks;
        static inline Lock lock;
    };
}


#endif //CPPMC_MAINTHREAD_H
