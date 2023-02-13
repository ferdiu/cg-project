
#pragma once

#include <iostream>
#include <algorithm>
#include <functional>
#include <optional>
#include <list>
#include <string>
#include <glm/glm.hpp>

#include "Components/Component.hpp"
#include "Components/Transform.hpp"

namespace FerdiuEngine
{

class GameObject
{
public:
    GameObject(::std::string name = "");

    // ------- GETTERS-SETTERS -------
    // active
    bool isActive();
    void setActive(bool v);

    // transform (is a component but with a special role)
    Transform getTransform();
    glm::vec3 getPosition();
    void setPosition(glm::vec3 v);
    glm::vec3 getScale();
    void setScale(glm::vec3 v);
    glm::vec3 getRotation();
    void setRotation(glm::vec3 v);
    glm::vec3 getGlobalPosition();

    // components
    std::list<Component> getComponents();
    bool hasComponent(Component c);
    void addComponents(Component c);
    void addComponents(Transform);
    void removeComponent(Component c);
    void removeComponent(int index);

    std::list<GameObject> getChildren();
    std::optional<GameObject> *getParent();

    bool isRoot();

private:
    std::string name;

    bool active = true;

    Transform transform;
    std::list<Component> components;
    std::list<Component>::iterator getComponentPosition(Component c);

    std::optional<GameObject> *parent = {};
    std::list<GameObject> children = std::list<GameObject>();
};

}
