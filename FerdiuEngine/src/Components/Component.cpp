
#include <uuid/uuid.h>

#include "../../include/Components/Component.hpp"

namespace FerdiuEngine
{

//---------------------- public -----------------------------------
Component::Component()
{
    uuid_generate(this->uuid);
}

bool Component::isEnabled()
{
    return enabled;
}
void Component::enable()
{
    enabled = true;
}
void Component::disable()
{
    enabled = false;
}

void Component::setOwner(GameObject *go)
{
    this->go = go;
    awake();
}
void Component::setGameObject(GameObject *go)
{
    setOwner(go);    // alias
}
GameObject *Component::getOwner()
{
    return go;
}
GameObject *Component::getGameObject()
{
    return getOwner();
}

GameObject& Component::getOwner() const
{
    return *go;
}
GameObject& Component::getGameObject() const
{
    return getOwner();
}

bool Component::awaken()
{
    return this->_awaken;
}

bool operator==(const Component& lhs, const Component& rhs) {
    return uuid_compare(lhs.uuid, rhs.uuid) == 0;
}

}
