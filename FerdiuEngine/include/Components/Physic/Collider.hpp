
#pragma once

#include "../Component.hpp"
#include "Bounds.hpp"

#include "../../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Collider : public Component
{
public:
    FERDIU_ENGINE_EXPORT Collider();

    FERDIU_ENGINE_EXPORT bool isTrigger();
    FERDIU_ENGINE_EXPORT void setTrigger(bool v);

    FERDIU_ENGINE_EXPORT Bounds *getBounds();
    FERDIU_ENGINE_EXPORT virtual bool checkCollision(Collider *c) = 0;

protected:
    FERDIU_ENGINE_EXPORT virtual void setBounds(Bounds *b);

private:
    bool trigger = false;

    Bounds *bounds;
};

}
