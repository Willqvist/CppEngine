//
// Created by Gerry on 2021-04-17.
//

#ifndef NETPROJECT_THREAD_H
#define NETPROJECT_THREAD_H

#include <functional>
#include <thread>
#include <threading/Lock.h>
#include <atomic>
namespace threading {
    typedef std::function<void()> ThreadFunction;
    /*
    struct ThreadData {
        bool _running = true;
        std::thread _thread;
        ~ThreadData() {
        
        }
    };
     */

    class Thread {
    public:
        //Thread() {}
        //Thread(Thread&& thread);
        //~Thread() = default;
        Thread(const ThreadFunction& run);
        void join();
        bool active();
        int id();

        static void sleep(int milliseconds);
        //static std::shared_ptr<ThreadData> instanceData();
    private:
        int _id;
        bool _running = true;
        Lock _threadLock;
        std::thread _thread;
        static int _ids;
        static Lock _lock;
        //static std::shared_ptr<ThreadData> threadData(int threadId);
        //static std::unordered_map<std::thread::id,int> _threads;
        //static std::unordered_map<int, std::shared_ptr<ThreadData>> _threadsId;
        //static std::unordered_map<
    };
}
#endif //NETPROJECT_THREAD_H
