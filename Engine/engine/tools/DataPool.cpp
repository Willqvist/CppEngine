//
// Created by Gerry on 2020-12-03.
//

#include "DataPool.h"

template<class Data, int capacity>
Data *VoxEng::DataPool<Data, capacity>::Rent(int size) {
    Block* b = nullptr;
    mutex.lock();
    for(Block& block : blocks) {
        if(block.end - block.start > size) {
            b = &block;
            break;
        }
    }
    if(b == nullptr) {
        mutex.unlock();
        return nullptr;
    }
    b.start = b.start+size;
    mutex.unlock();

    return &data[b.start];

}

template<class Data, int capacity>
void VoxEng::DataPool<Data, capacity>::Return(Data* data, int size) {

}
