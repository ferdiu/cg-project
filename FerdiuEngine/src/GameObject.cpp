
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

namespace FerdiuEngine
{

//---------------------- public -----------------------------------

GameObject::GameObject(std::string name)
{
    this->name = name;
}

// ------- GETTERS-SETTERS -------
// active
bool GameObject::isActive()
{
    return active;
}
void GameObject::setActive(bool v)
{
    active = v;
}

// transform (is a component but with a special role)
Transform GameObject::getTransform()
{
    return transform;
}
glm::vec3 GameObject::getPosition()
{
    return this->transform.getPosition();
}
void GameObject::setPosition(glm::vec3 v)
{
    this->transform.setPosition(v);
}
glm::vec3 GameObject::getScale()
{
    return this->transform.getScale();
}
void GameObject::setScale(glm::vec3 v)
{
    this->transform.setScale(v);
}
glm::vec3 GameObject::getRotation()
{
    return this->transform.getRotation();
}
void GameObject::setRotation(glm::vec3 v)
{
    this->transform.setRotation(v);
}
glm::vec3 GameObject::getGlobalPosition()
{
    glm::vec3 pos = glm::vec3(getPosition());
    std::optional<GameObject> *p = parent;

    while (p->has_value()) {
        pos += p->value().getPosition();
        p = p->value().getParent();
    }

    return pos;
}

// components
std::list<Component> GameObject::getComponents()
{
    return components;
}
bool GameObject::hasComponent(Component c)
{
    return getComponentPosition(c) != components.end();
}
void GameObject::addComponents(Component c)
{
    components.push_back(c);
}
void GameObject::addComponents(Transform)
{
    throw std::invalid_argument("Can't have an other Transform in a single GameObject.");
}
void GameObject::removeComponent(Component c)
{
    if (hasComponent(c))
        components.erase(getComponentPosition(c));
}
void GameObject::removeComponent(int index)
{
    std::list<Component>::iterator it = components.begin();
    advance(it, index);
    components.erase(it);
}

std::list<GameObject> GameObject::getChildren()
{
    return children;
}
std::optional<GameObject> *GameObject::getParent()
{
    return parent;
}

bool GameObject::isRoot()
{
    return !(parent->has_value());
}

//---------------------- private -----------------------------------

std::list<Component>::iterator GameObject::getComponentPosition(Component c)
{
    return find(components.begin(), components.end(), c);
}

}
