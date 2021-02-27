//
// Created by Gerry on 2021-02-27.
//

#ifndef CPPMC_PIPELINE_H
#define CPPMC_PIPELINE_H

#include <vector>
#include <functional>
#include "PipelineObject.h"

template<class In, class Out>
class Pipeline {
public:
    template<class I,class O>
    const Pipeline<I,O>* next(const Ref<PipelineObject<I,O>>& obj) {
        //pipeline.push_back(obj);
        return (Pipeline<I,O>*)this;
    }

    void insert(const In& in) {
        //pipeline[0].insert(in);
    }

    void finish(std::function<void(Out&)> done) {

    }

private:
    //std::vector<PipelineObject<void,void>> pipeline;
};
#endif //CPPMC_PIPELINE_H
