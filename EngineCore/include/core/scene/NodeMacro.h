//
// Created by Gerry on 2021-05-22.
//

#ifndef CPPMC_NODEMACRO_H
#define CPPMC_NODEMACRO_H
#define NODEIMPL(inst) template class Node<inst>;
#define ISCLASS(inst, inherit) \
private: \
    std::string _className = #inst; \
    static inline size_t _sHashedClassName = std::hash<std::string>{}(#inst); \
    size_t _hashedClassName = _sHashedClassName; \
    static inline std::string _sClassName = #inst; \
protected: \
    virtual bool isClassHashed(size_t hash) override { \
        return hash == inst::_hashedClassName ? true : inherit::isClassHashed(hash); \
    } \
public: \
    virtual std::string& getClass() override { \
        return inst::_className;\
    } \
    static inline std::string& GetClass() { \
        return inst::_sClassName; \
    } \
    static inline size_t HashClassName() { \
        return inst::_sHashedClassName; \
    } \
    virtual bool isClass(const std::string& val) override { \
        size_t hash = std::hash<std::string>{}(val); \
        return hash == inst::_hashedClassName ? true : inherit::isClassHashed(hash); \
    }
#endif //CPPMC_NODEMACRO_H
