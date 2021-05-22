//
// Created by Gerry on 2021-05-15.
//

#ifndef CPPMC_TREE_H
#define CPPMC_TREE_H

#include <vector>
#include <string>
#include <functional>
#include <core/Memory.h>
//TODO: change to node in array instead of "linked list" to speed up iteration.
namespace Ziti {
    namespace Structure {
        /*
        class TreeNode;

        class TreePath {
        private:

            TreePath() {};
            TreePath()

            TreeNode* _parent;
            std::string& name;
        };

        template<class T>
        class TreeNode {
        public:

            TreeNode() {
                _UUID = _GUUID++;
            }

            //TODO: try to omptimze away Ref!
            TreePath add(const std::string& name, T value) {
                TreeNode<T> node = new TreeNode<T>();
                _path =
                node->_value = value;
                node->_level = _level + 1;
                node->_path = _path.append(name);
                _children.push_back(node);
                return node->_path;
            }

            TreePath add(TreePath& path, T value) {
                TreeNode<T> node;
                node->_value = value;
                node->_level = _level + 1;
                node->_path = _path.append(path);
                _children.push_back(node);
                return node->_path;
            }

            TreeNode<T>& get(TreePath& path) {
                //TODO: speed up checking!!
            }


            T& getValue(TreePath& name) {

            }

            void iterate(const std::function<void(TreeNode<T>&)>& func) {
                for(TreeNode<T>& child : _children) {
                    func(child);
                    child->iterate(func);
                }
            }

            std::vector<TreeNode<T>>& children() {
                return _children;
            }

            unsigned int uuid() {
                return _UUID;
            }

            bool isLeaf() {
                return _children.empty();
            }

            T value() { return _value; }

        protected:
            std::vector<TreeNode<T>*> _children;
            T _value;
            int _level = 0;
            int _UUID = 0;
            TreePath _path;
            static inline unsigned int _GUUID = 0;
        };
         */
    }
}

#endif //CPPMC_TREE_H
