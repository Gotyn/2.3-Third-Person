#include <cassert>
#include <iostream>
using namespace std;

#include <glm.hpp>

#include "mge/core/Timer.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"

GameObject::GameObject(std::string pName, glm::vec3 pPosition, bool pAddToWorld )
:	_name( pName ), _transform( glm::translate( pPosition ) ),  _parent(NULL), _children()
{
    if (pAddToWorld == true)
        World::Instance()->add(this);
}

GameObject::~GameObject()
{
    //detach all children
    cout << "GC running on:" << _name << endl;

    while (_children.size() > 0) {
        GameObject* child = _children[0];
        remove (child);
        delete child;
    }

    //do not forget to delete behaviour, material, mesh, collider manually if required!
//    while (_behaviours.size() > 0) {
//        AbstractBehaviour* b = _behaviours[0];
//        delete b;
//    }
}

void GameObject::setName (std::string pName)
{
    _name = pName;
}

std::string GameObject::getName() const
{
	return _name;
}

void GameObject::setTransform (const glm::mat4& pTransform)
{
    _transform = pTransform;
}

glm::mat4& GameObject::getTransform()
{
    return _transform;
}

glm::vec3 GameObject::getForward()
{
    glm::vec4 f = _transform * glm::vec4(0,0,-1,0);
    return glm::vec3(f[0],f[1],f[2]);
}

glm::vec3 GameObject::getUp()
{
    glm::vec4 f = _transform * glm::vec4(0,1,0,0);
    return glm::vec3(f[0],f[1],f[2]);
}

void GameObject::setLocalPosition (glm::vec3 pPosition)
{
    _transform[3] = glm::vec4 (pPosition,1);
}

void GameObject::setLocalPositionLua (float x, float y, float z)
{
    setLocalPosition(glm::vec3(x,y,z));
}

glm::vec3 GameObject::getLocalPosition()
{
	return glm::normalize(glm::vec3(_transform[3]));
}

void GameObject::LookAt(GameObject* pTarget)
{
    setTransform(
        glm::inverse (
            glm::lookAt (getWorldPosition(), pTarget->getWorldPosition(), glm::vec3(0,1,0))
        )
    );

//    glm::vec3 forward = glm::normalize(getLocalPosition() - pTarget->getLocalPosition());
//    glm::vec3 right = glm::cross (glm::vec3(0,1,0), forward);
//    glm::vec3 up = glm::cross (forward, right);
//
//    setTransform(
//      glm::mat4 (glm::vec4(right,0), glm::vec4(up,0), glm::vec4(forward,0), glm::vec4(getLocalPosition(),1) )
//    );
}

//new multiple behaviours
void GameObject::addBehaviour(AbstractBehaviour* pBehaviour)
{
    pBehaviour->setOwner(this);

    if (_behaviours.count(&typeid(*pBehaviour)) == 0)
        _behaviours[&typeid(*pBehaviour)] = pBehaviour;
    else
        std::cout << "Component already exists!" << std::endl;
}

void GameObject::setParent (GameObject* pParent) {
    //remove from previous parent
    if (_parent != NULL) {
        _parent->_innerRemove(this);
        _parent = NULL;
    }

    //set new parent
    if (pParent != NULL) {
        _parent = pParent;
        _parent->_innerAdd(this);
        //pass on world to child
    }
}

GameObject* GameObject::getParent() {
    return _parent;
}

void GameObject::_innerAdd(GameObject* pChild)
{
    //set new parent
    pChild->_parent = this;
	_children.push_back(pChild);
}

void GameObject::_innerRemove (GameObject* pChild) {
    for (auto i = _children.begin(); i != _children.end(); ++i) {
        if (*i == pChild) {
            (*i)->_parent = NULL;
            _children.erase(i);
            return;
        }
    }
}

void GameObject::add (GameObject* pChild) {
    pChild->setParent(this);
}

void GameObject::remove (GameObject* pChild) {
    pChild->setParent(NULL);
}

////////////

glm::vec3 GameObject::getWorldPosition()
{
	return glm::vec3(getWorldTransform()[3]);
}

glm::mat4& GameObject::getWorldTransform()
{
    return _worldTransform;
}

////////////

void GameObject::translate(glm::vec3 pTranslation)
{
	setTransform(glm::translate(_transform, pTranslation));
}

void GameObject::move(float x, float y, float z)
{
    translate(glm::vec3(x, y, z) * Timer::deltaTime());
}

void GameObject::scale(glm::vec3 pScale)
{
	setTransform(glm::scale(_transform, pScale));
}

void GameObject::scaleLua(float x, float y, float z)
{
    setTransform(glm::scale(_transform, glm::vec3(x, y, z)));
}

void GameObject::rotate(float pAngle, glm::vec3 pAxis)
{
	setTransform(glm::rotate(_transform, pAngle, pAxis));
}

void GameObject::update(float pStep, const glm::mat4& pParentTransform)
{
    _worldTransform = pParentTransform * _transform;

    for (auto const& value: _behaviours)
    {
        value.second->update(pStep);
    }

    for (int i = _children.size()-1; i >= 0; --i ) {
        _children[i]->update(pStep, _worldTransform);
    }
}

int GameObject::getChildCount() {
    return _children.size();
}

GameObject* GameObject::getChildAt(int pIndex) {
    return _children[pIndex];
}

