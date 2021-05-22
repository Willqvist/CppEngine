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
            if(_dirtyLocal) {
                _local.update();
                _dirtyLocal = false;
            }
            return _local;
        }

        Transform global() {
            if(_dirty) updateGlobal();
            return _global;
        }

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

        void translate(glm::vec3& pos) { Dirtify
            _local.position() += pos;
        }


        void update() override {

            if(_spatial && _spatial->_dirty) {
                _base = _spatial->global();
                updateGlobal();
                _spatial->_dirty = false;
                _dirty = true;
            }

        }

        /*
        void enterTree(SceneTree* tree) override {
            _spatial = parent<Spatial>();
        }
         */

    private:
        void updateGlobal() {
            _local.update();
            _global = _base.changeOfBasis(_local);
            _dirty = false;
            _dirtyLocal = false;
        }
        bool _dirty = false, _dirtyLocal = false;
        Transform _local;
        Transform _base;
        Transform _global;
        Ref<Spatial> _spatial;

    };
}


#endif //CPPMC_SPATIAL_H
