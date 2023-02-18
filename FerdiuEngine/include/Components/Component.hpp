
#pragma once

#include <iostream>
#include <uuid/uuid.h>

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

// forward declaration
class GameObject;

class FERDIU_ENGINE_EXPORT Component
{
public:
    FERDIU_ENGINE_EXPORT Component();
    FERDIU_ENGINE_EXPORT virtual ~Component() {};

    FERDIU_ENGINE_EXPORT bool enabled();
    FERDIU_ENGINE_EXPORT void enable();
    FERDIU_ENGINE_EXPORT void disable();

    FERDIU_ENGINE_EXPORT GameObject *getOwner();
    FERDIU_ENGINE_EXPORT GameObject *getGameObject();
    FERDIU_ENGINE_EXPORT GameObject& getOwner() const;
    FERDIU_ENGINE_EXPORT GameObject& getGameObject() const;
    FERDIU_ENGINE_EXPORT bool hasOwner() const;
    FERDIU_ENGINE_EXPORT bool hasGameObject() const;

    // events
    FERDIU_ENGINE_EXPORT bool awaken();
    FERDIU_ENGINE_EXPORT bool left();
    FERDIU_ENGINE_EXPORT bool destroyed();

    FERDIU_ENGINE_EXPORT virtual void awake() { _awaken = true; _left = false; };
    FERDIU_ENGINE_EXPORT virtual void start() {};

    FERDIU_ENGINE_EXPORT virtual void physicsUpdatePre() {};
    FERDIU_ENGINE_EXPORT virtual void physicsUpdatePost() {};
    FERDIU_ENGINE_EXPORT virtual void update() {};

    FERDIU_ENGINE_EXPORT virtual void fixedUpdate() {};

    FERDIU_ENGINE_EXPORT virtual void leave() { _left = true; _awaken = false; };

    FERDIU_ENGINE_EXPORT virtual void draw() {};

    FERDIU_ENGINE_EXPORT virtual void destroy() {};
    FERDIU_ENGINE_EXPORT void destroyImmediate();

    // operators
    FERDIU_ENGINE_EXPORT friend bool operator==(const Component& lhs, const Component& rhs);

private:
    bool _awaken = false;
    bool _left = false;

    bool _destroyed = false;

    uuid_t uuid;

    bool _enabled = true;

    GameObject *go;

    void setOwner(GameObject *go);
    void setGameObject(GameObject *go);

    friend GameObject;
};

}
