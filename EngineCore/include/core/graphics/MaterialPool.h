//
// Created by Gerry on 2021-05-29.
//

#ifndef CPPMC_MATERIALPOOL_H
#define CPPMC_MATERIALPOOL_H

namespace Ziti {
    template<class T, int size>
    class MaterialPool {
    public:
        MaterialPool() {
            for(int i = 0; i < size; i++) {
                _pool.push_back(CreateRef<T>());
                _free.push_back(true);
            }
        }
        Ref<T> get() {
            int i = findFree(true);
            if(i < 0) return nullptr;
            _free[i] = false;
            return _pool[i];
        }
        void put(Ref<T>& value) {
            int i = findFree(false);
            _free[i] = true;
            _pool[i] = value;
        }
    private:
        int findFree(bool free) {
            for(int i = 0; i < _free.size(); i++)
                if(free && _free[i])
                    return i;
                else if(!free && !_free[i])
                    return i;
            return -1;
        }
        std::vector<Ref<T>> _pool;
        std::vector<bool> _free;
    };
}


#endif //CPPMC_MATERIALPOOL_H
