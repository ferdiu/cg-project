
#include <iostream>
#include <algorithm>
#include <functional>
#include <optional>
#include <list>
#include <string>
#include <glm/glm.hpp>

#include "../include/Components/Component.hpp"
#include "../include/Components/Transform.hpp"
#include "../include/GameObject.hpp"
#include "../include/Components/Camera.hpp"
#include "Components/Renderer.hpp"

namespace FerdiuEngine
{

//---------------------- public -----------------------------------

GameObject::GameObject(std::string name)
{
    this->name = name;
}

// ------- GETTERS-SETTERS -------
// active
bool GameObject::isActive() const
{
    return active;
}
void GameObject::setActive(bool v)
{
    active = v;

    if (v) awake();
}

// name
std::string GameObject::getName() const
{
    return this->name;
}
void GameObject::setName(std::string name)
{
    this->name = name;
}

// transform (is a component but with a special role)
Transform *GameObject::getTransform()
{
    return &transform;
}
glm::vec3 GameObject::getPosition() const
{
    return this->transform.getPosition();
}
void GameObject::setPosition(glm::vec3 v)
{
    this->transform.setPosition(v);
}
glm::vec3 GameObject::getScale() const
{
    return this->transform.getScale();
}
void GameObject::setScale(glm::vec3 v)
{
    this->transform.setScale(v);
}
glm::vec3 GameObject::getRotation() const
{
    return this->transform.getRotation();
}
void GameObject::setRotation(glm::vec3 v)
{
    this->transform.setRotation(v);
}
glm::vec3 GameObject::getGlobalPosition() const
{
    glm::vec3 pos = glm::vec3(getPosition());
    std::optional<GameObject*> p = parent;

    while (p.has_value()) {
        pos += p.value()->getPosition();
        p = p.value()->getParent();
    }

    return pos;
}

// components
std::list<Component*> GameObject::getComponents()
{
    return components;
}
bool GameObject::hasComponent(Component *c)
{
    return getComponentPosition(c) != components.end();
}
GameObject *GameObject::addComponent(Component *c)
{
    components.push_back(c);
    c->setOwner(this);

    return this;
}
GameObject *GameObject::addComponent(Transform*)
{
    throw std::invalid_argument("Can't have an other Transform in a single GameObject.");

    return this;
}
void GameObject::removeComponent(Component *c)
{
    if (hasComponent(c))
        components.erase(getComponentPosition(c));

    c->setOwner(nullptr);
}
void GameObject::removeComponent(int index)
{
    std::list<Component*>::iterator it = components.begin();
    advance(it, index);
    components.erase(it);
}

std::list<GameObject*> GameObject::getChildren()
{
    return children;
}
std::optional<GameObject*> GameObject::getParent()
{
    return parent;
}

bool GameObject::isRoot() const
{
    return !(parent.has_value()) && instantiated();
}

void GameObject::draw()
{
#ifdef DEBUG_VERBOSE
    Debug::indent();
    Debug::Log("start->draw: " + name);
#endif

    Camera *c = Camera::getCurrent();
    glm::mat4 *m = new glm::mat4(1);

    if (nullptr == c)
        return;

    c->pushMatrices();

    m = c->applyModelMatrix(transform);

    std::list<GameObject*>::iterator childIter;
    for (childIter = children.begin(); childIter != children.end(); ++childIter)
        if ((*childIter)->isActive())
            (*childIter)->draw();

    if (this->renderer().has_value())
    {
        Renderer *r = this->renderer().value();
        r->draw();
        r->setModelMatrix(*m);
    }

    c->popMatrices();

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->draw: " + name);
    Debug::unindent();
#endif
}

std::optional<Renderer*> GameObject::renderer()
{
    return this->_renderer;
}
std::optional<Collider*> GameObject::collider()
{
    return this->_collider;
}
std::optional<RigidBody*> GameObject::rigidbody()
{
    return this->_rigidbody;
}

GameObject *GameObject::addRenderer(Renderer *r)
{
    this->_renderer = r;
    r->setOwner(this);

    return this;
}
GameObject *GameObject::addCollider(Collider *c)
{
    this->_collider = c;
    c->setOwner(this);

    return this;
}
GameObject *GameObject::addRigidbody(RigidBody *rb)
{
    this->_rigidbody = rb;
    rb->setOwner(this);

    return this;
}

void GameObject::awake()
{
#ifdef DEBUG_VERBOSE
    Debug::indent();
    Debug::Log("start->awake: " + name);
#endif

    std::list<GameObject*>::iterator childIter;
    for (childIter = children.begin(); childIter != children.end(); ++childIter)
        if ((*childIter)->isActive())
            (*childIter)->awake();

    std::list<Component*>::iterator compIter;
    for (compIter = components.begin(); compIter != components.end(); ++compIter)
        if ((*compIter)->isEnabled() && !(*compIter)->awaken())
            (*compIter)->awake();

    if (!getTransform()->awaken())
        getTransform()->awake();

    // TODO: ugly, remove this in the future
    if (renderer().has_value() && renderer().value()->isEnabled() && !renderer().value()->awaken())
        renderer().value()->awake();

    if (collider().has_value() && collider().value()->isEnabled() && !collider().value()->awaken())
        collider().value()->awake();

    if (rigidbody().has_value() && rigidbody().value()->isEnabled() && !rigidbody().value()->awaken())
        rigidbody().value()->awake();
    //

    start();

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->awake: " + name);
    Debug::unindent();
#endif
}
void GameObject::start()
{
#ifdef DEBUG_VERBOSE
    Debug::indent();
    Debug::Log("start->start: " + name);
#endif

    std::list<GameObject*>::iterator childIter;
    for (childIter = children.begin(); childIter != children.end(); ++childIter)
        if ((*childIter)->isActive())
            (*childIter)->start();

    std::list<Component*>::iterator compIter;
    for (compIter = components.begin(); compIter != components.end(); ++compIter)
        if ((*compIter)->isEnabled())
            (*compIter)->start();

    getTransform()->start();

    // TODO: ugly, remove this in the future
    if (renderer().has_value() && renderer().value()->isEnabled())
        renderer().value()->start();

    if (collider().has_value() && collider().value()->isEnabled())
        collider().value()->start();

    if (rigidbody().has_value() && rigidbody().value()->isEnabled())
        rigidbody().value()->start();
    //

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->start: " + name);
    Debug::unindent();
#endif
}

void GameObject::fixedUpdate()
{
#ifdef DEBUG_VERBOSE
    Debug::indent();
    Debug::Log("start->fixedUpdate: " + name);
#endif

    std::list<GameObject*>::iterator childIter;
    for (childIter = children.begin(); childIter != children.end(); ++childIter)
        if ((*childIter)->isActive())
            (*childIter)->fixedUpdate();

    std::list<Component*>::iterator compIter;
    for (compIter = components.begin(); compIter != components.end(); ++compIter)
        if ((*compIter)->isEnabled())
            (*compIter)->fixedUpdate();

    getTransform()->fixedUpdate();

    // TODO: ugly, remove this in the future
    if (renderer().has_value() && renderer().value()->isEnabled())
        renderer().value()->fixedUpdate();

    if (collider().has_value() && collider().value()->isEnabled())
        collider().value()->fixedUpdate();

    if (rigidbody().has_value() && rigidbody().value()->isEnabled())
        rigidbody().value()->fixedUpdate();
    //

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->fixedUpdate: " + name);
    Debug::unindent();
#endif

}
void GameObject::update()
{
#ifdef DEBUG_VERBOSE
    Debug::indent();
    Debug::Log("start->update: " + name);
#endif

    std::list<GameObject*>::iterator childIter;
    for (childIter = children.begin(); childIter != children.end(); ++childIter)
        if ((*childIter)->isActive())
            (*childIter)->update();

    std::list<Component*>::iterator compIter;
    for (compIter = components.begin(); compIter != components.end(); ++compIter)
        if ((*compIter)->isEnabled())
            (*compIter)->update();

    getTransform()->update();

    // TODO: ugly, remove this in the future
    if (renderer().has_value() && renderer().value()->isEnabled())
        renderer().value()->update();

    if (collider().has_value() && collider().value()->isEnabled())
        collider().value()->update();

    if (rigidbody().has_value() && rigidbody().value()->isEnabled())
        rigidbody().value()->update();
    //

#ifdef DEBUG_VERBOSE
    Debug::Log("finish->update: " + name);
    Debug::unindent();
#endif
}

void GameObject::setScene(Scene *s)
{
    this->scene = s;
}

bool GameObject::instantiated() const
{
    return this->scene.has_value();
}
GameObject *GameObject::instantiate(GameObject *parent)
{
    this->parent = parent;
    this->parent.value()->addChild(this);
    this->scene = parent->scene;


    if (isActive())
        awake();

    return this;
}

void GameObject::destroy()
{
    this->parent.value()->removeChild(this);
    this->parent = nullptr;
    this->scene = nullptr;
}

bool GameObject::hasChild(GameObject *c)
{
    return getChildPosition(c) != children.end();

}
void GameObject::addChild(GameObject *c)
{
    children.push_back(c);
}
void GameObject::removeChild(GameObject *c)
{
    if (hasChild(c))
        children.erase(getChildPosition(c));
}

bool operator==(const GameObject& lhs, const GameObject& rhs) {
    return lhs.transform == rhs.transform;
}

//---------------------- private -----------------------------------

std::list<Component*>::iterator GameObject::getComponentPosition(Component *c)
{
    return find(components.begin(), components.end(), c);
}

std::list<GameObject*>::iterator GameObject::getChildPosition(GameObject *c)
{
    return find(children.begin(), children.end(), c);
}

}
