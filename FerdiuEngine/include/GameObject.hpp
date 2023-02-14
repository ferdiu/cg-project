
#pragma once

#include <iostream>
#include <algorithm>
#include <functional>
#include <optional>
#include <list>
#include <string>
#include <glm/glm.hpp>

#include "Components/Component.hpp"
#include "Components/Renderer.hpp"
#include "Components/Transform.hpp"
#include "Components/Physic/Collider.hpp"
#include "Components/Physic/RigidBody.hpp"

#include "FerdiuEngine_export.h"


namespace FerdiuEngine
{

class Scene;

class FERDIU_ENGINE_EXPORT GameObject
{
public:
    FERDIU_ENGINE_EXPORT GameObject(::std::string name = "");

    // ------- GETTERS-SETTERS -------
    // active
    FERDIU_ENGINE_EXPORT bool isActive();
    FERDIU_ENGINE_EXPORT void setActive(bool v);

    // name
    FERDIU_ENGINE_EXPORT ::std::string getName();
    FERDIU_ENGINE_EXPORT void setName(::std::string name);

    // transform (is a component but with a special role)
    FERDIU_ENGINE_EXPORT Transform *getTransform();
    FERDIU_ENGINE_EXPORT glm::vec3 getPosition();
    FERDIU_ENGINE_EXPORT void setPosition(glm::vec3 v);
    FERDIU_ENGINE_EXPORT glm::vec3 getScale();
    FERDIU_ENGINE_EXPORT void setScale(glm::vec3 v);
    FERDIU_ENGINE_EXPORT glm::vec3 getRotation();
    FERDIU_ENGINE_EXPORT void setRotation(glm::vec3 v);
    FERDIU_ENGINE_EXPORT glm::vec3 getGlobalPosition();

    // components
    FERDIU_ENGINE_EXPORT std::list<Component*> getComponents();
    FERDIU_ENGINE_EXPORT bool hasComponent(Component *c);
    FERDIU_ENGINE_EXPORT void addComponent(Component *c);
    FERDIU_ENGINE_EXPORT void addComponent(Transform*);
    FERDIU_ENGINE_EXPORT void removeComponent(Component *c);
    FERDIU_ENGINE_EXPORT void removeComponent(int index);

    FERDIU_ENGINE_EXPORT std::list<GameObject*> getChildren();
    FERDIU_ENGINE_EXPORT std::optional<GameObject*> getParent();

    FERDIU_ENGINE_EXPORT bool isRoot();

    FERDIU_ENGINE_EXPORT void draw();

    // TODO: ugly but functional for a small project (in future will use a map and a list)
    FERDIU_ENGINE_EXPORT std::optional<Renderer*> renderer();
    FERDIU_ENGINE_EXPORT std::optional<Collider*> collider();
    FERDIU_ENGINE_EXPORT std::optional<RigidBody*> rigidbody();

    FERDIU_ENGINE_EXPORT GameObject *addRenderer(Renderer *r);
    FERDIU_ENGINE_EXPORT GameObject *addCollider(Collider *c);
    FERDIU_ENGINE_EXPORT GameObject *addRigidbody(RigidBody *rb);

    // events
    FERDIU_ENGINE_EXPORT void awake();
    FERDIU_ENGINE_EXPORT void start();

    FERDIU_ENGINE_EXPORT void fixedUpdate();
    FERDIU_ENGINE_EXPORT void update();

    // TODO: ugly (too exposed)
    FERDIU_ENGINE_EXPORT void setScene(Scene *s);

    FERDIU_ENGINE_EXPORT bool instantiated();
    FERDIU_ENGINE_EXPORT GameObject *instantiate(GameObject *parent);
    FERDIU_ENGINE_EXPORT void destroy();

    FERDIU_ENGINE_EXPORT bool hasChild(GameObject *c);
    FERDIU_ENGINE_EXPORT void addChild(GameObject *c);
    FERDIU_ENGINE_EXPORT void removeChild(GameObject *c);

    // OPERATORS
    FERDIU_ENGINE_EXPORT friend bool operator==(const GameObject& lhs, const GameObject& rhs);

private:
    std::string name;

    bool active = true;

    Transform transform;
    std::list<Component*> components = std::list<Component*>();
    std::list<Component*>::iterator getComponentPosition(Component *c);

    std::optional<Scene*> scene = {};
    std::optional<GameObject*> parent = {};
    std::list<GameObject*> children = std::list<GameObject*>();

    std::list<GameObject*>::iterator getChildPosition(GameObject *c);

    std::optional<Renderer*> _renderer = {};
    std::optional<Collider*> _collider = {};
    std::optional<RigidBody*> _rigidbody = {};
};

}
