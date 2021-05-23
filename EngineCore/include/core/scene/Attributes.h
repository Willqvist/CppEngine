//
// Created by Gerry on 2021-05-23.
//

#ifndef CPPMC_ATTRIBUTES_H
#define CPPMC_ATTRIBUTES_H

#include <variant>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <functional>
#include <core/Transform.h>
namespace Ziti {
    typedef std::variant<glm::vec3,int,float,bool,glm::vec2,std::string, Transform> Types;
    typedef std::function<void(Types)> TypeFunction;
    #define VISIT(type) virtual void visit(const std::string& name, type* value) = 0;
    #define DEFVISIT(type) void operator()(type& val) {  type* ptr = (type*)data;  visitor->visit(name,ptr); }
    class AttributeVisitor {
    public:
        VISIT(glm::vec3)
        VISIT(glm::vec2)
        VISIT(int)
        VISIT(float)
        VISIT(bool)
        VISIT(std::string)
        VISIT(Transform)
    };

    struct VisitorStruct {
        AttributeVisitor* visitor;
        std::string name;
        TypeFunction func;
        void* data;
        DEFVISIT(glm::vec3)
        DEFVISIT(glm::vec2)
        DEFVISIT(int)
        DEFVISIT(float)
        DEFVISIT(bool)
        DEFVISIT(std::string)
        DEFVISIT(Transform)
    };

    struct TypeData {
        Types data;
        void* rlData;
        std::string name;
    };


    class Attributes {
    public:

        Attributes(AttributeVisitor* visitor) : _listener(visitor) {
            _visitor.visitor = _listener;
        };

        template<class T>
        void emplace(const std::string& name, T* value) {
            //_visitor.name = name;
            //std::visit(_visitor,value);
            //Types& t = (Types&)value;
            //_fncmap[name] = func;
            _types.push_back({*value,value, name});
        }

        void visitAll() {
            for(TypeData& t : _types) {
                _visitor.name = t.name;
                _visitor.data = t.rlData;
                std::visit(_visitor, t.data);

            }

            _types.clear();
        }
    private:
        VisitorStruct _visitor;
        AttributeVisitor* _listener;
        std::vector<TypeData> _types;
        std::unordered_map<std::string,TypeFunction> _fncmap;

    };
}


#endif //CPPMC_ATTRIBUTES_H
