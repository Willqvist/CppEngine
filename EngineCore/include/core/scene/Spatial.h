//
// Created by Gerry on 2021-05-16.
//

#ifndef CPPMC_SPATIAL_H
#define CPPMC_SPATIAL_H

#include "Node.h"
#define Dirtify _dirtyLocal = true; _dirty = true;
namespace Ziti {
    class Spatial : public Node {
        ISCLASS(Spatial,Node)
        Transform local() {
            return _local;
        }

        Transform global() {
            return _global;
        }

        virtual void onPositionChange() {};

        void start() override {
            /*
            listenFromParent("spatial::tm",[&](NodeMessage& msg){
                //TODO:: update transform from node;
                Spatial* spatial = (Spatial*)msg.emitter;
                _base = spatial->global();
                updateGlobal();
            });
             */
        }

        /*
        void translate(const glm::vec3& pos) {
            _local.position() += pos;
        }

        void set(const glm::vec3& pos) {
            _local.position() = pos;
        }
         */

        void checkIsDirty() {
            if(!glm::all(glm::equal(_localCtrl.position(),_local.position()))) {
                _dirty = true;
                _localCtrl = _local;
                _local.update();
                updateGlobal();
                printf("dirty!!\n");
                onPositionChange();
            }
        }

        void update() override {
            if(_dirty) {
                _dirty = false;
            }
            checkIsDirty();
            //printf("spatial: %p\n",_spatial);
            if(_spatial && _spatial->_dirty) {
                printf("parent is dirty!! %s\n",getClass().c_str());
                _base = _spatial->global();
                updateGlobal();
                _dirty = true;
                onPositionChange();
            }

            if(_dirty) {
                _dirtyIter ++;
                if(_dirtyIter == 2) {
                    _dirtyIter = 0;
                    _dirty = false;
                }
            } else {
                _dirtyIter = 0;
            }

        }

        void attributes(Attributes &attributes) override {
            Node::attributes(attributes);
            attributes.emplace<Transform>("Transform",&_local);
        }


        void enterTree(SceneTree* tree) override {
            _spatial = parent<Spatial>();
        }


    private:
        void updateGlobal() {
            _base.update();
            _local.update();
            _global = _local.changeOfBasis(_base);
        }
        bool _dirty = false;
        bool _prevDirtyFix = false;
        int _dirtyIter = 0;
        Transform _local;
        Transform _base;
        Transform _global;
        Transform _localCtrl;
        Ref<Spatial> _spatial;

    };
}


#endif //CPPMC_SPATIAL_H
