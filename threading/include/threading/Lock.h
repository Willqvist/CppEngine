//
// Created by Gerry on 2021-04-17.
//

#ifndef NETPROJECT_LOCK_H
#define NETPROJECT_LOCK_H
#include <mutex>

namespace threading {
    using KeySession =  std::unique_lock<std::mutex>;
    class Lock {
    public:
        KeySession use();
        void wait(KeySession& key);
        void notify();
        void notifyAll();

    private:
        std::mutex mtx;
        std::condition_variable condLock;
    };
}

#endif //NETPROJECT_LOCK_H
