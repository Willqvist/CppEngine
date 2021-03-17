//
// Created by Gerry on 2021-02-27.
//

#ifndef CPPMC_PIPELINEOBJECT_H
#define CPPMC_PIPELINEOBJECT_H

#include <functional>

template<class I, class O>
class PipelineObject {
public:
    void finish(std::function<void(O&)> func) {
        pip = std::move(func);
    }
    void insert(I& val) {
        onInsert(val);
    }
protected:
    void send(O& val) {
        pip(val);
    }
    virtual void onInsert(I& val) = 0;
private:
    std::function<void(O&)> pip;
};
#endif //CPPMC_PIPELINEOBJECT_H
