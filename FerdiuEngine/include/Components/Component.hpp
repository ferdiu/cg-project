
#pragma once

#include <uuid/uuid.h>

namespace FerdiuEngine
{

// forward declaration
class GameObject;

class Component
{
public:
    Component();

    bool isEnabled();
    void enable();
    void disable();

    void setOwner(GameObject *go);
    void setGameObject(GameObject *go);
    GameObject *getOwner();
    GameObject *getGameObject();

    friend bool operator==(const Component& lhs, const Component& rhs);
private:
    uuid_t uuid;

    bool enabled = true;

    GameObject *go;
};

}
