//
// Created by Gerry on 2021-05-06.
//

#ifndef CPPMC_MEMORY_H
#define CPPMC_MEMORY_H

#include <memory>
#include <utility>
namespace Ziti {
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T,typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
    template<typename T>
    constexpr Ref<T> CreateRef(T* pointer) {
        return std::shared_ptr<T>(pointer);
    }

    template<typename T,typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    enum class Ownership {
        Yes, No
    };

}
#endif //CPPMC_MEMORY_H
