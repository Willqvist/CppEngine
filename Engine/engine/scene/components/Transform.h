//
// Created by Gerry on 2020-08-26.
//

#ifndef CPPMC_TRANSFORM_H
#define CPPMC_TRANSFORM_H

#include <glm/vec3.hpp>
#include <scene/Registry.h>
#include <glm/ext/quaternion_float.hpp>
#include <math/Vector3.h>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <scene/Entity.h>

namespace VoxEng {
    enum class TransformType {
        POSITION,ROTATION,SCALE
    };

    class Transform {
    public:
        Transform() {
            setRotation(0,0,0);
        }

        glm::vec3 right() {
            return mRight;
        }

        glm::vec3 up() {
            return mUp;
        }

        glm::vec3 forward() {
            return mForward;
        }

        glm::quat toQuaternion() {
            float radX = glm::radians(rotation().x);
            float radY = glm::radians(rotation().y);
            float radZ = glm::radians(rotation().z);
            glm::quat angX = glm::angleAxis(radX, Vector3::right());
            glm::quat angY = glm::angleAxis(radY, Vector3::up());
            glm::quat angZ = glm::angleAxis(radZ, Vector3::forward());
            return angX*angY*angZ;
        }

        glm::vec3 forwardXZ() {
            return forward()*glm::vec3(1,0,1);
        }

        void setPosition(const glm::vec3& value) {
            set(TransformType::POSITION,value);
        }

        void setScale(const glm::vec3& value) {
            set(TransformType::SCALE,value);
        }

        void setRotation(const glm::vec3& value) {
            set(TransformType::ROTATION,value);
        }

        void setPosition(float x,float y,float z) {
            setX(TransformType::POSITION,x);
            setY(TransformType::POSITION,y);
            setZ(TransformType::POSITION,z);
        }

        void setScale(float x,float y,float z) {
            setX(TransformType::SCALE,x);
            setY(TransformType::SCALE,y);
            setZ(TransformType::SCALE,z);
        }

        void setRotation(float x,float y,float z) {
            setX(TransformType::ROTATION,x);
            setY(TransformType::ROTATION,y);
            setZ(TransformType::ROTATION,z);
        }

        void translatePosition(const glm::vec3& value) {
            translate(TransformType::POSITION,value);
        }

        void translateScale(const glm::vec3& value) {
            translate(TransformType::ROTATION,value);
        }

        void translateRotation(const glm::vec3& value) {
            translate(TransformType::SCALE,value);
        }

        void translatePosition(float x,float y,float z) {
            translateX(TransformType::POSITION,x);
            translateY(TransformType::POSITION,y);
            translateZ(TransformType::POSITION,z);
        }

        void translateScale(float x,float y,float z) {
            translateX(TransformType::SCALE,x);
            translateY(TransformType::SCALE,y);
            translateZ(TransformType::SCALE,z);
        }

        void translateRotation(float x,float y,float z) {
            translateX(TransformType::ROTATION,x);
            translateY(TransformType::ROTATION,y);
            translateZ(TransformType::ROTATION,z);
            constraint(TransformType::ROTATION);
        }

        void set(TransformType type, const glm::vec3& value) {
            getTransformType(type) = value;
            dirty = true;
        }

        void setX(TransformType type, float value) {
            getTransformType(type).x = value;
            dirty = true;
        }

        void setY(TransformType type, float value) {
            getTransformType(type).y = value;
            dirty = true;
        }

        void setZ(TransformType type, float value) {
            getTransformType(type).z = value;
            dirty = true;
        }

        void translate(TransformType type, const glm::vec3& value) {
            getTransformType(type) += value;
            dirty = true;
        }

        void translateX(TransformType type, float value) {
            getTransformType(type).x += value;
            constraint(type);
            dirty = true;
        }

        void translateY(TransformType type, float value) {
            getTransformType(type).y += value;
            dirty = true;
        }

        void translateZ(TransformType type, float value) {
            getTransformType(type).z += value;
            dirty = true;
        }

        const glm::vec3 scale() {
            if(dirty) updateWorldPosition(parent());
            return mScale;
        }

        const glm::vec3 rotation() {
            if(dirty) updateWorldPosition(parent());
            return mRotation;
        }

        const glm::vec3 position() {
            if(dirty) updateWorldPosition(parent());
            return mPosition;
        }

        const glm::vec3 localScale() {
            return mLocalScale;
        }

        const glm::vec3 localRotation() {
            return mLocalRotation;
        }

        const glm::vec3 localPosition() {
            return mLocalPosition;
        }

        operator glm::mat4 () {
            return createMatrix();
        }
    private:

        glm::mat4 createRotMatrix(const glm::vec3& position,const glm::vec3& scale,const glm::vec3& rotation) {
            glm::mat4 out = glm::mat4(1.0f);
            out = glm::rotate(out, glm::radians(-rotation.x), Vector3::right());
            out = glm::rotate(out, glm::radians(-rotation.y), Vector3::up());
            out = glm::rotate(out, glm::radians(-rotation.z), Vector3::forward());
            out = glm::translate(out, -position);
            out = glm::scale(out, scale);
            return out;
        }

        glm::vec3& getTransformType(TransformType type) {
            switch(type) {
                case TransformType::POSITION: return mLocalPosition;
                case TransformType::ROTATION: return mLocalRotation;
                case TransformType::SCALE: return mLocalScale;
            }
        }

        void constraint(TransformType type) {
            switch(type) {
                case TransformType::ROTATION: {
                    if(mLocalRotation.x > 360) mLocalRotation.x = mLocalRotation.x-360;
                    if(mLocalRotation.x < 0) mLocalRotation.x = 360+mLocalRotation.x;
                    if(mLocalRotation.y > 360) mLocalRotation.y = mLocalRotation.y-360;
                    if(mLocalRotation.y < 0) mLocalRotation.y = 360+mLocalRotation.y;
                    if(mLocalRotation.z > 360) mLocalRotation.z = mLocalRotation.z-360;
                    if(mLocalRotation.z < 0) mLocalRotation.z = 360+mLocalRotation.z;
                };
            }
        }

        Transform* parent() {
            Transform* parent = nullptr;
            if(!parentEntity.valid() || !parentEntity.hasComponent<Transform>())
                return parent;

            parent = &parentEntity.getComponent<Transform>();
            return parent;
        }

        bool hasChanged(Transform* parent) {
            if(dirty) {
                return true;
            }
            if(parent != nullptr) {
                return parent->hasChanged(parent->parent()) || parent->prevDirty;
            }
            return false;
        }

        void updateWorldPosition(Transform* parent) {
            mPosition = mLocalPosition;
            mRotation = mLocalRotation;
            mScale = mLocalScale;
            dirty = false;
            if(hasChanged(this)) {
                glm::mat4 rotMat = createRotMatrix(mPosition, mScale, mRotation);
                glm::mat4 inv = glm::inverse(rotMat);
                mForward = glm::normalize(glm::vec3(inv[2]));
                mRight = glm::normalize(glm::vec3(inv[0]));
                mUp = glm::normalize(glm::vec3(inv[1]));
            }

            //TODO: CALCULATE position with parent base.
            if(parent) {
                parent->createMatrix();
                //DEBUG_LOG("UP: %s",to_string(parent->up()).c_str());
                mPosition = mLocalPosition.x*parent->right() + mLocalPosition.y*parent->up() + mLocalPosition.z * parent->forward();
                mRotation = mLocalRotation + parent->rotation();
                mScale = mLocalScale* parent->scale();
            }
            //id = parent->createMatrix() * id;
        }

        glm::mat4 createMatrix() {
            bool hasParent = false;
            Transform* parent = this->parent();
            prevDirty = false;
            if(!hasChanged(parent)) {
                return transform;
            }
            prevDirty = true;
            //DEBUG_LOG("HAS CHANGED: %d", parent && parent->hasChanged());
            updateWorldPosition(parent);
            glm::mat4 id = fillTransformMatrix();

            //DEBUG_LOG("scale: %s - %s",to_string(mPosition).c_str(),to_string(mLocalPosition).c_str());

            oldPosition = mLocalPosition;
            oldRotation = mLocalRotation;
            oldScale = mLocalScale;
/*
            glm::mat4 rotMat = createRotMatrix(mPosition,mScale,mRotation);
            glm::mat4 inv = glm::inverse(rotMat);
            mForward = glm::normalize(glm::vec3(inv[2]));
            mRight = glm::normalize(glm::vec3(inv[0]));
            mUp = glm::normalize(glm::vec3(inv[1]));
*/

            transform = id;
            return id;
        }

        glm::mat4 fillTransformMatrix() const {
            glm::mat4 id = glm::mat4(1.0f);
            id = glm::translate(id, mPosition);
            id = glm::rotate(id, glm::radians(mRotation.x), glm::vec3(1.0f, 0, 0));
            id = glm::rotate(id, glm::radians(mRotation.y), glm::vec3(0, 1.0f, 0));
            id = glm::rotate(id, glm::radians(mRotation.z), glm::vec3(0, 0, 1.0f));
            id = glm::scale(id, mScale);
            return id;
        }

        glm::mat4 transform;
        glm::vec3 oldPosition = glm::vec3(0,0,0);
        glm::vec3 oldRotation = glm::vec3(0,0,0);
        glm::vec3 oldScale = glm::vec3(1,1,1);

        glm::vec3 mUp = glm::vec3(1,1,1);
        glm::vec3 mRight = glm::vec3(1,1,1);
        glm::vec3 mForward = glm::vec3(1,1,1);


        glm::vec3 mPosition = glm::vec3(0,0,0);
        glm::vec3 mRotation = glm::vec3(0,0,0);
        glm::vec3 mScale = glm::vec3(1,1,1);

        glm::vec3 mLocalPosition = glm::vec3(0, 0, 0);
        glm::vec3 mLocalRotation = glm::vec3(0, 0, 0);
        glm::vec3 mLocalScale = glm::vec3(1, 1, 1);

        bool dirty = false;
        bool prevDirty = false;

        Entity parentEntity;

        friend class Scene;
    };
}
#endif //CPPMC_TRANSFORM_H
