//
// Created by Gerry on 2021-03-16.
//
#include "Transform.h"
#include <scene/Registry.h>

VoxEng::Transform::Transform() {
    setRotation(0,0,0);
}

glm::vec3 VoxEng::Transform::right()  {
    return mRight;
}

glm::vec3 VoxEng::Transform::up() {
    return mUp;
}

glm::vec3 VoxEng::Transform::forward() {
    return mForward;
}

glm::quat VoxEng::Transform::toQuaternion() {
    float radX = glm::radians(rotation().x);
    float radY = glm::radians(rotation().y);
    float radZ = glm::radians(rotation().z);
    glm::quat angX = glm::angleAxis(radX, Vector3::right());
    glm::quat angY = glm::angleAxis(radY, Vector3::up());
    glm::quat angZ = glm::angleAxis(radZ, Vector3::forward());
    return angX*angY*angZ;
}

glm::vec3 VoxEng::Transform::forwardXZ() {
    return forward()*glm::vec3(1,0,1);
}

void VoxEng::Transform::setPosition(const glm::vec3 &value) {
    set(TransformType::POSITION,value);
}

void VoxEng::Transform::setScale(const glm::vec3 &value){
    set(TransformType::SCALE,value);
}

void VoxEng::Transform::setRotation(const glm::vec3 &value) {
    set(TransformType::ROTATION,value);
}

void VoxEng::Transform::setPosition(float x, float y, float z) {
    setX(TransformType::POSITION,x);
    setY(TransformType::POSITION,y);
    setZ(TransformType::POSITION,z);
}

void VoxEng::Transform::setScale(float x, float y, float z) {
    setX(TransformType::SCALE,x);
    setY(TransformType::SCALE,y);
    setZ(TransformType::SCALE,z);
}

void VoxEng::Transform::setRotation(float x, float y, float z) {
    setX(TransformType::ROTATION,x);
    setY(TransformType::ROTATION,y);
    setZ(TransformType::ROTATION,z);
}

void VoxEng::Transform::translatePosition(const glm::vec3 &value) {
    translate(TransformType::POSITION,value);
}

void VoxEng::Transform::translateScale(const glm::vec3 &value) {
    translate(TransformType::ROTATION,value);
}

void VoxEng::Transform::translateRotation(const glm::vec3 &value) {
    translate(TransformType::SCALE,value);
}

void VoxEng::Transform::translatePosition(float x, float y, float z) {
    translateX(TransformType::POSITION,x);
    translateY(TransformType::POSITION,y);
    translateZ(TransformType::POSITION,z);
}

void VoxEng::Transform::translateScale(float x, float y, float z) {
    translateX(TransformType::SCALE,x);
    translateY(TransformType::SCALE,y);
    translateZ(TransformType::SCALE,z);
}

void VoxEng::Transform::translateRotation(float x, float y, float z) {
    translateX(TransformType::ROTATION,x);
    translateY(TransformType::ROTATION,y);
    translateZ(TransformType::ROTATION,z);
    constraint(TransformType::ROTATION);
}

void VoxEng::Transform::set(VoxEng::TransformType type, const glm::vec3 &value) {
    getTransformType(type) = value;
    dirty = true;
}

void VoxEng::Transform::setX(VoxEng::TransformType type, float value) {
    getTransformType(type).x = value;
    dirty = true;
}

void VoxEng::Transform::setY(VoxEng::TransformType type, float value) {
    getTransformType(type).y = value;
    dirty = true;
}

void VoxEng::Transform::setZ(VoxEng::TransformType type, float value) {
    getTransformType(type).z = value;
    dirty = true;
}

void VoxEng::Transform::translate(VoxEng::TransformType type, const glm::vec3 &value) {
    getTransformType(type) += value;
    dirty = true;
}

void VoxEng::Transform::translateX(VoxEng::TransformType type, float value) {
    getTransformType(type).x += value;
    constraint(type);
    dirty = true;
}

void VoxEng::Transform::translateY(VoxEng::TransformType type, float value) {
    getTransformType(type).y += value;
    dirty = true;
}

void VoxEng::Transform::translateZ(VoxEng::TransformType type, float value) {
    getTransformType(type).z += value;
    dirty = true;
}

const glm::vec3 VoxEng::Transform::scale() {
    if(dirty) updateWorldPosition();
    return mScale;
}

const glm::vec3 VoxEng::Transform::rotation() {
    if(dirty) updateWorldPosition();
    return mRotation;
}

const glm::vec3 VoxEng::Transform::position() {
    if(dirty) updateWorldPosition();
    return mPosition;
}

const glm::vec3 VoxEng::Transform::localScale() {
    return mLocalScale;
}

const glm::vec3 VoxEng::Transform::localRotation() {
    return mLocalRotation;
}

const glm::vec3 &VoxEng::Transform::localPosition() {
    return mLocalPosition;
}

VoxEng::Transform::operator glm::mat4() {
    return createMatrix();
}

glm::mat4
VoxEng::Transform::createRotMatrix(const glm::vec3 &position, const glm::vec3 &scale, const glm::vec3 &rotation) {
    glm::mat4 out = glm::mat4(1.0f);
    out = glm::rotate(out, glm::radians(-rotation.x), Vector3::right());
    out = glm::rotate(out, glm::radians(-rotation.y), Vector3::up());
    out = glm::rotate(out, glm::radians(-rotation.z), Vector3::forward());
    out = glm::translate(out, -position);
    out = glm::scale(out, scale);
    return out;
}

glm::vec3 &VoxEng::Transform::getTransformType(VoxEng::TransformType type) {
    switch(type) {
        case TransformType::POSITION: return mLocalPosition;
        case TransformType::ROTATION: return mLocalRotation;
        case TransformType::SCALE: return mLocalScale;
    }
    return mLocalPosition;
}

void VoxEng::Transform::constraint(VoxEng::TransformType type) {
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

bool VoxEng::Transform::validParent()
{
    return hasParent && parentEntity.hasComponent<Transform>();
}

VoxEng::Transform &VoxEng::Transform::parent() {
    return parentEntity.getComponent<Transform>();
}

bool VoxEng::Transform::hasChanged() {
    if (dirty)
        return true;
    if(validParent()) {
        Transform& parent = this->parent();
        return parent.hasChanged() || parent.prevDirty;
    }
    return false;
}

void VoxEng::Transform::updateWorldPosition() {
    mPosition = mLocalPosition;
    mRotation = mLocalRotation;
    mScale = mLocalScale;
    if(hasChanged()) {
        glm::mat4 rotMat = createRotMatrix(mPosition, mScale, mRotation);
        glm::mat4 inv = glm::inverse(rotMat);
        mForward = glm::normalize(glm::vec3(inv[2]));
        mRight = glm::normalize(glm::vec3(inv[0]));
        mUp = glm::normalize(glm::vec3(inv[1]));
    }
    dirty = false;
    //TODO: CALCULATE position with parent base.
    if(validParent()) {
        Transform& parent = this->parent();
        parent.createMatrix();
        //DEBUG_LOG("UP: %s",to_string(parent->up()).c_str());
        mPosition = mLocalPosition.x*parent.right() + mLocalPosition.y*parent.up() + mLocalPosition.z * parent.forward();
        mRotation = mLocalRotation + parent.rotation();
        mScale = mLocalScale* parent.scale();
    }
    //id = parent->createMatrix() * id;
}

glm::mat4 VoxEng::Transform::createMatrix() {
    prevDirty = false;
    if (!hasChanged()) {
        return transform;
    }
    prevDirty = true;
    //DEBUG_LOG("HAS CHANGED: %d", parent && parent->hasChanged());
    updateWorldPosition();
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

glm::mat4 VoxEng::Transform::fillTransformMatrix() const {
    glm::mat4 id = glm::mat4(1.0f);
    id = glm::translate(id, mPosition);
    id = glm::rotate(id, glm::radians(mRotation.x), glm::vec3(1.0f, 0, 0));
    id = glm::rotate(id, glm::radians(mRotation.y), glm::vec3(0, 1.0f, 0));
    id = glm::rotate(id, glm::radians(mRotation.z), glm::vec3(0, 0, 1.0f));
    id = glm::scale(id, mScale);
    return id;
}

void VoxEng::Transform::setParent(VoxEng::Entity &ent)
{
    hasParent = true;
    parentEntity = ent;
}
