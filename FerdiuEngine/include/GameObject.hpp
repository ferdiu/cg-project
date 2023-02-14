
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

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT GameObject
{
public:
    FERDIU_ENGINE_EXPORT GameObject(::std::string name = "");

    // ------- GETTERS-SETTERS -------
    // active
    FERDIU_ENGINE_EXPORT bool isActive();
    FERDIU_ENGINE_EXPORT void setActive(bool v);

    // transform (is a component but with a special role)
    FERDIU_ENGINE_EXPORT Transform getTransform();
    FERDIU_ENGINE_EXPORT glm::vec3 getPosition();
    FERDIU_ENGINE_EXPORT void setPosition(glm::vec3 v);
    FERDIU_ENGINE_EXPORT glm::vec3 getScale();
    FERDIU_ENGINE_EXPORT void setScale(glm::vec3 v);
    FERDIU_ENGINE_EXPORT glm::vec3 getRotation();
    FERDIU_ENGINE_EXPORT void setRotation(glm::vec3 v);
    FERDIU_ENGINE_EXPORT glm::vec3 getGlobalPosition();

    // components
    FERDIU_ENGINE_EXPORT std::list<Component> getComponents();
    FERDIU_ENGINE_EXPORT bool hasComponent(Component c);
    FERDIU_ENGINE_EXPORT void addComponents(Component c);
    FERDIU_ENGINE_EXPORT void addComponents(Transform);
    FERDIU_ENGINE_EXPORT void removeComponent(Component c);
    FERDIU_ENGINE_EXPORT void removeComponent(int index);

    FERDIU_ENGINE_EXPORT std::list<GameObject> getChildren();
    FERDIU_ENGINE_EXPORT std::optional<GameObject> *getParent();

    FERDIU_ENGINE_EXPORT bool isRoot();

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
