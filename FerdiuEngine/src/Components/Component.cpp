
#include <uuid/uuid.h>

#include "../../include/Components/Component.hpp"

namespace FerdiuEngine
{

//---------------------- public -----------------------------------
Component::Component()
{
    uuid_generate(this->uuid);
}

bool Component::enabled()
{
    return _enabled;
}
void Component::enable()
{
    _enabled = true;
}
void Component::disable()
{
    _enabled = false;
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

bool Component::hasOwner() const
{
    return nullptr != go;
}

bool Component::hasGameObject() const
{
    return hasOwner();
}

bool Component::awaken()
{
    return this->_awaken;
}

bool Component::left()
{
    return this->_left;
}

bool Component::destroyed()
{
    return this->_destroyed;
}

void Component::destroyImmediate()
{
    delete this;
}

bool operator==(const Component& lhs, const Component& rhs) {
    return uuid_compare(lhs.uuid, rhs.uuid) == 0;
}

//---------------------- private -----------------------------------
void Component::setOwner(GameObject *go)
{
    this->go = go;
    awake();
}
void Component::setGameObject(GameObject *go)
{
    setOwner(go);
}

}
