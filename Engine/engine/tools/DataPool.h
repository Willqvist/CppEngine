//
// Created by Gerry on 2020-12-03.
//

#ifndef CPPMC_DATAPOOL_H
#define CPPMC_DATAPOOL_H
#include <mutex>
#include <unordered_map>
namespace VoxEng {
    class Block {
        public:
            int start;
            int end;
    };
    template<class Data, int capacity>
    class DataPool {
    public:
        Data *Rent(int size);

        void Return(Data* data, int size);

    private:
        Data data[capacity];
        std::vector<Block> blocks;
        std::mutex mutex;
    };
}


#endif //CPPMC_DATAPOOL_H
