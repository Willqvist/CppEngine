//
// Created by Gerry on 2021-05-15.
//

#include "core/scene/Node.h"



void Ziti::Node::emit(const std::string &name, Ziti::NodeMessageValue value) {
    if(_listeningNodes.find(name) == _listeningNodes.end()) return;
    std::vector<Node*> listeners = _listeningNodes[name];
    for(auto& listener : listeners) {
        NodeMessage msg;
        msg.emitter = this;
        msg.value = value;
        msg.key = name;
        //msg.isParent = listener._node->getParent().get() == this;
        listener->_messages.push_back(msg);
    }
}

void Ziti::Node::listenFromParent(const std::string &key, Ziti::NodeListener listener) {
    parent()->addNewListeningNode(key,this);
    if(_listeners.find(key) == _listeners.end())
        _listeners[key] = {};
    _listeners[key].push_back(listener);
}

const void Ziti::Node::onUpdate() {
    for(auto& msg : _messages) {
        std::string& key = msg.key;
        if(_listeners.find(key) != _listeners.end()) {
            for(auto& listener : _listeners[key]) {
                listener(msg);
            }
        }
    }

    //TODO: only works for children to listen now due to message clear.
    // check if message was for parent, then dont clear!!.
    _messages.clear();
    update();
}

const void Ziti::Node::addNewListeningNode(const std::string &name, Ziti::Node *node) {
    if(_listeningNodes.find(name) == _listeningNodes.end())
        _listeningNodes[name] = {};
    _listeningNodes[name].push_back(node);
}
