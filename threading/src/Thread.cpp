//
// Created by Gerry on 2021-04-17.
//
#include <threading/Thread.h>
#define data Thread::threadData(_id)
#define ifisnull if(Thread::threadData(_id) == nullptr)
namespace threading {

    Thread::Thread(const ThreadFunction &run) {
        //std::shared_ptr<ThreadData> _data = std::shared_ptr<ThreadData>(new ThreadData());

        {
            Thread::_lock.use();
            _id = Thread::_ids++;
            //Thread::_threadsId[_id] = _data;
        }
        int id = _id;

        _thread = std::thread([run ,id]() {
            {
                //Thread::_lock.use();
                //if (Thread::_threadsId[id] == nullptr) return;
                //Thread::_threads[std::this_thread::get_id()] = id;
            }
            run();
        });

    }

    void Thread::join() {
        {
            _threadLock.use();
            if (!_running) return;
            _running = false;
        }
        {
            //Thread::_lock.use();
            //Thread::_threadsId[_id] = nullptr;
        }
        _thread.join();
    }

    void Thread::sleep(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    bool Thread::active() {
        return _running;
    }

    int Thread::id() {
        return _id;
    }

    /*
    std::shared_ptr<ThreadData> Thread::instanceData() {
        std::thread::id id = std::this_thread::get_id();
        if (_threads.find(id) == _threads.end())
            return nullptr;

        return Thread::threadData(Thread::_threads[id]);
    }
     */

    int Thread::_ids = 0;
    Lock Thread::_lock = Lock();

    //TODO: make so map uses multiple keys, not two maps.
   // std::unordered_map<std::thread::id, int> Thread::_threads = {};
   // std::unordered_map<int, std::shared_ptr<ThreadData>> Thread::_threadsId = {};
/*
    std::shared_ptr<ThreadData> Thread::threadData(int threadId) {
            return Thread::_threadsId[threadId];
    }
*/
 }