//
// Created by Gerry on 2021-04-16.
//
#include <threading/ThreadManager.h>
namespace threading {
    std::unique_ptr<ThreadInstance> ThreadManager::start(const ThreadFunction &function) {
        _lock.use();
        int id = ThreadManager::_usedIds++;
        std::unique_ptr<ThreadInstance> inst = std::unique_ptr<ThreadInstance>(new ThreadInstance(function,id));
        ThreadInstance* ptr = inst.get();
        std::unique_ptr<Thread> thread = std::make_unique<Thread>([ptr,id,this]() {
            std::unique_ptr<Thread>& thrd = this->_threads[id];

            while(ptr && thrd && thrd->active()) {
                ptr->_func();
            }
        });

        _threads[id] = std::move(thread);
        return inst;
    }

    void ThreadManager::stop(const std::unique_ptr<ThreadInstance>& thread) {
        ThreadManager::join(thread);
    }

    void ThreadManager::join(const std::unique_ptr<ThreadInstance>& thread) {
        _lock.use();
        std::unique_ptr<Thread>& t = _threads[thread->_id];
        t->join();
    }

    void ThreadManager::joinAll() {
        _lock.use();
        for(auto& val : _threads) {
            std::unique_ptr<Thread>& t = val.second;
            //t.stop();
            t->join();
        }
    }


    ThreadManager &ThreadManager::instance() {
        static const std::unique_ptr<ThreadManager> instance{new ThreadManager()};
        return *instance;
    }

    ThreadManager::~ThreadManager() {
        joinAll();
    }

}