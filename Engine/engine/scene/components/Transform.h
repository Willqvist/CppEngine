//
// Created by Gerry on 2020-08-26.
//

#ifndef CPPMC_TRANSFORM_H
#define CPPMC_TRANSFORM_H

#include <glm/vec3.hpp>
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
        Transform();
        glm::vec3 right();
        glm::vec3 up();
        glm::vec3 forward();
        glm::quat toQuaternion();
        glm::vec3 forwardXZ();
        void setPosition(const glm::vec3& value);
        void setScale(const glm::vec3& value);
        void setRotation(const glm::vec3& value);

        void setPosition(float x,float y,float z);

        void setScale(float x,float y,float z);

        void setRotation(float x,float y,float z);

        void translatePosition(const glm::vec3& value);

        void translateScale(const glm::vec3& value);

        void translateRotation(const glm::vec3& value);

        void translatePosition(float x,float y,float z);

        void translateScale(float x,float y,float z);
        void translateRotation(float x,float y,float z);

        const glm::vec3 scale();

        const glm::vec3 rotation();

        const glm::vec3 position();

        const glm::vec3 localScale();
        const glm::vec3 localRotation();

        const glm::vec3& localPosition();

        operator glm::mat4 ();
    private:

        void set(TransformType type, const glm::vec3& value);

        void setX(TransformType type, float value);

        void setY(TransformType type, float value);

        void setZ(TransformType type, float value);

        void translate(TransformType type, const glm::vec3& value);

        void translateX(TransformType type, float value);

        void translateY(TransformType type, float value);

        void translateZ(TransformType type, float value);

        glm::mat4 createRotMatrix(const glm::vec3& position,const glm::vec3& scale,const glm::vec3& rotation);

        glm::vec3& getTransformType(TransformType type);

        void constraint(TransformType type);

    	bool validParent();

        Transform& parent();

        bool hasChanged();
        void updateWorldPosition();

        glm::mat4 createMatrix();
        glm::mat4 fillTransformMatrix() const;

        void setParent(Entity& ent);
    	
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
        bool hasParent = false;
        Entity parentEntity;

        friend class Scene;
    };
}
#endif //CPPMC_TRANSFORM_H
