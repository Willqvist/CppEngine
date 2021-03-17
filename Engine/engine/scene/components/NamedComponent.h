//
// Created by Gerry on 2020-08-26.
//

#ifndef CPPMC_NAMEDCOMPONENT_H
#define CPPMC_NAMEDCOMPONENT_H

#include <string>
namespace VoxEng {
    class NamedComponent {
    public:
        std::string mName, mTag;
        unsigned int id;

        NamedComponent();

        void name(const std::string &name);

        std::string &name();

    private:
        static int globalId;
    };
}
#endif //CPPMC_NAMEDCOMPONENT_H
