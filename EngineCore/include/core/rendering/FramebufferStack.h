//
// Created by Gerry on 2021-05-15.
//

#ifndef CPPMC_FRAMEBUFFERSTACK_H
#define CPPMC_FRAMEBUFFERSTACK_H

#include <stack>
namespace Ziti {
    class FramebufferStack {
    public:
        static void push(unsigned int id);
        static void pop();
    private:
        static std::stack<unsigned int> _stack;
    };
}


#endif //CPPMC_FRAMEBUFFERSTACK_H
