//
// Created by Gerry on 2021-05-15.
//

#include <glad/glad.h>
#include "core/rendering/FramebufferStack.h"
#include <cassert>

std::stack<unsigned int> Ziti::FramebufferStack::_stack;

void Ziti::FramebufferStack::push(unsigned int id) {
    //TODO:: change to correct api call!!
    glBindFramebuffer(GL_FRAMEBUFFER,id);
    _stack.push(id);
}

void Ziti::FramebufferStack::pop() {
    _stack.pop();
    if(_stack.empty()) {
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        return;
    }
    unsigned int val = _stack.top();
    glBindFramebuffer(GL_FRAMEBUFFER,val);
}
