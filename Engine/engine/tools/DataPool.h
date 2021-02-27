//
// Created by Gerry on 2020-12-03.
//

#ifndef CPPMC_DATAPOOL_H
#define CPPMC_DATAPOOL_H
#include <mutex>
#include <unordered_map>
#include <threading/Lock.h>

namespace VoxEng {
    template<class Data, int capacityPerBuffer, int buffers>
    class DataPool {
    public:

        Data* WaitRent() {
            Data * dat = Rent();
            if(dat == nullptr) {
                {
                    KeyLock key = lock.lock();
                    while (dat == nullptr) {
                        lock.wait(key);
                        dat = _Rent();
                    }
                }
            }
            return dat;
        }

    	Data* GetIndex(int pool) // not thread safe, used only when knowledge of no overlap.
        {
            return &data[pool*capacityPerBuffer];
        }

        Data *Rent() {
            KeyLock key = lock.lock();
            Data* dat = _Rent();
            return dat;            
        }

        void Return(Data *data) {
            {
                KeyLock key = lock.lock();
                int offset = (data - this->data) / (capacityPerBuffer * sizeof(Data));
                if (offset < 0 || offset >= buffers)
                {
                    return;
                }
                usedBuffers[offset] = false;
            }
            lock.notify();
        }

    private:
        Data* _Rent() {
            int start = -1;
            for(int i = 0; i < buffers; i++) {
                if(!usedBuffers[i]) {
                    start = i*capacityPerBuffer;
                    usedBuffers[i] = true;
                    break;
                }
            }
            if(start == -1) {
                return nullptr;
            }
            return &data[start];
        }
        Data data[capacityPerBuffer * buffers];
        bool usedBuffers[buffers];
        Lock lock;
    };
}


#endif //CPPMC_DATAPOOL_H
