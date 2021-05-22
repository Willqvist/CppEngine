//
// Created by Gerry on 2021-05-15.
//

#ifndef CPPMC_NODE_H
#define CPPMC_NODE_H

#include <core/rendering/RenderEngine.h>
#include <string.h>
#include <functional>
#include "NodeMacro.h"

namespace Ziti {
    class Node;
    class SceneTree;
    typedef void* NodeMessageValue;
    struct NodeMessage {
        Node* emitter;
        bool isParent;
        std::string key;
        NodeMessageValue value;
    };

    typedef std::function<void(NodeMessage&)> NodeListener;
    struct NodeMessageListener {
        NodeListener _fnc;
    };

    class Object {
    public:
        virtual std::string& getClass() {
            return _name;
        }

        static std::string& GetClass() {
            return _name;
        }

        virtual bool isClass(const std::string& val) {
            return false;
        }
    protected:
        virtual bool isClassHashed(size_t hash) {
            return false;
        }
    private:
        static inline std::string _name = "Object";
    };

    class Node : public std::enable_shared_from_this<Node>, public Object {
        ISCLASS(Node,Object)

        Node() : _name(typeid(this).name()) {
        }

        /*
        template<class T>
        inline static Ref<T> getNode() {
            return getNode<T>(typeid(T).name());
        }

        template<class T>
        inline  static Ref<Node> getNode(const std::string& name) {

        }
         */

        template<class T>
        Ref<T> addNode() {
            Ref<T> node = CreateRef<T>();
            node->_parent = shared_from_this();
            node->start();
            node->setSceneTree(_tree);
            _children.push_back(node);
            return node;
        }


        template<class T>
        Ref<T> findFirst() {
            std::string& name = T::GetClass();
            for(Ref<Node>& child : _children) {
                if(child->isClass(name))
                    return std::static_pointer_cast<T>(child);
                Ref<T> val = child->findFirst<T>();
                if(val != nullptr)
                    return val;
            }
            return nullptr;
        }


        template<class T>
        Ref<T> parent() {
            return std::static_pointer_cast<T>(_parent);
        }

        Ref<Node> parent() {
            return _parent;
        }

        SceneTree* getSceneTree() {
            return _tree;
        }

        void setSceneTree(SceneTree* tree) {
            _tree = tree;
            enterTree(_tree);
            //TODO: iterate over all children(deep) and call enterTree and leaveTree with old tree.
        }

        std::vector<Ref<Node>>& children() {
            return _children;
        }

        //message
        void emit(const std::string& name, NodeMessageValue value);
        void listenFromParent(const std::string& key, NodeListener listener);

        const void onUpdate();

        //overriables
        virtual void start() {};
        virtual void update() {};
        virtual void render(RenderEngine& engine) {};
        virtual void enterTree(SceneTree* tree) {};
        virtual void leaveTree(SceneTree* tree) {};

        virtual ~Node() = default;

    private:
        const void addNewListeningNode(const std::string& name, Node* node);

        std::string _name;
        SceneTree* _tree;

        Ref<Node> _parent;
        std::vector<Ref<Node>> _children;

        std::vector<NodeMessage> _messages;
        std::unordered_map<std::string, std::vector<NodeListener>> _listeners;
        std::unordered_map<std::string, std::vector<Node*>> _listeningNodes;

        friend class SceneTree;
        //std::unordered_map<std::string, std::vector<std::function<void(NodeMessage)>>> _listener;
    };
}


#endif //CPPMC_NODE_H
