
#pragma once

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

    FERDIU_ENGINE_EXPORT friend bool operator==(const Component& lhs, const Component& rhs);
private:
    uuid_t uuid;

    bool enabled = true;

    GameObject *go;
};

}
