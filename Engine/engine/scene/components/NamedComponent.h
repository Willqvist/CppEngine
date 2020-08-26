//
// Created by Gerry on 2020-08-26.
//

#ifndef CPPMC_NAMEDCOMPONENT_H
#define CPPMC_NAMEDCOMPONENT_H

#include <string>

class NamedComponent {
public:
    std::string mName,mTag;
    unsigned int id;
    NamedComponent() {
        id = globalId ++;
    }
    void name(const std::string& name) {
        this->mName = name;
    }

    std::string& name() {
        return mName;
    }

private:
    inline static int globalId = 0;
};
#endif //CPPMC_NAMEDCOMPONENT_H
