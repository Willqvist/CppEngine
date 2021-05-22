//
// Created by Gerry on 2021-04-16.
//

#ifndef NETPROJECT_THREADMANAGER_H
#define NETPROJECT_THREADMANAGER_H

#include <threading/Thread.h>
#include <thread>
#include <threading/Lock.h>
#include <atomic>
namespace threading {

    class ThreadInstance {
    private:
        ThreadInstance(const ThreadFunction& func, int id) : _func(func), _id(id) {}

        ThreadFunction _func;
        int _id;
        friend class ThreadManager;
    };

    class ThreadManager {
    public:
        std::unique_ptr<ThreadInstance> start(const ThreadFunction& function);
        void stop(const std::unique_ptr<ThreadInstance>& thread);
        void join(const std::unique_ptr<ThreadInstance>& thread);
        void joinAll();

        static ThreadManager& instance();

        ThreadManager(const ThreadManager&) = delete;
        ThreadManager& operator= (const ThreadManager) = delete;
        ~ThreadManager();
    private:
        ThreadManager() {}
        int _usedIds = 0;
        std::unordered_map<int,std::unique_ptr<Thread>> _threads = {};
        Lock _lock;
    };
}
#endif //NETPROJECT_THREADMANAGER_H
