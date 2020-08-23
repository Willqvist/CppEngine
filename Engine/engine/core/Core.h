//
// Created by Gerry on 2020-08-10.
// Inspiration hazel engine,
//

#ifndef CPPMC_CORE_H
#define CPPMC_CORE_H

#include <memory>
namespace VoxEng {
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T,typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T,typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}

#define BIND_FN(fn) std::bind(&fn,this,std::placeholders::_1)
#define BIND_LAMBDA(fn) [&](auto&&... args)-> bool{return this->fn(std::forward<decltype(args)>(args)...);}
#ifdef G_OPENGL
#define GRAPHICS_LIBRARY Library::OPENGL
#else
#error No graphics library macro set, use [G_OPENGL|G_DIRECTX]
#endif


#endif //CPPMC_CORE_H
