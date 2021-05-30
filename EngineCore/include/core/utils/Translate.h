//
// Created by Gerry on 2021-05-28.
//

#ifndef CPPMC_TRANSLATE_H
#define CPPMC_TRANSLATE_H
template<class Val, class Target>
class Translate {
public:
    Target& target() {
        return _target;
    }

    Val& target() {
        return _value;
    }



private:
    Val _value;
    Target _target;
};
#endif //CPPMC_TRANSLATE_H
