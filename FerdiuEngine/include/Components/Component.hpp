
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

    FERDIU_ENGINE_EXPORT bool isEnabled();
    FERDIU_ENGINE_EXPORT void enable();
    FERDIU_ENGINE_EXPORT void disable();

    FERDIU_ENGINE_EXPORT void setOwner(GameObject *go);
    FERDIU_ENGINE_EXPORT void setGameObject(GameObject *go);
    FERDIU_ENGINE_EXPORT GameObject *getOwner();
    FERDIU_ENGINE_EXPORT GameObject *getGameObject();
    FERDIU_ENGINE_EXPORT GameObject& getOwner() const;
    FERDIU_ENGINE_EXPORT GameObject& getGameObject() const;

    // events
    FERDIU_ENGINE_EXPORT virtual bool awaken();

    FERDIU_ENGINE_EXPORT virtual void awake() { _awaken = true; };
    FERDIU_ENGINE_EXPORT virtual void start() {};

    FERDIU_ENGINE_EXPORT virtual void fixedUpdate() {};
    FERDIU_ENGINE_EXPORT virtual void update() {};

    FERDIU_ENGINE_EXPORT friend bool operator==(const Component& lhs, const Component& rhs);
private:
    bool _awaken = false;

    uuid_t uuid;

    bool enabled = true;

    GameObject *go;
};

}
