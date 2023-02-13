
#pragma once

#include "../Component.hpp"
#include "Bounds.hpp"

namespace FerdiuEngine
{

class Collider : Component
{
public:
    bool isTrigger();
    void setTrigger(bool v);

    Bounds getBounds();
    virtual bool checkCollision(Collider c);

protected:
    virtual void setBounds(Bounds b);

private:
    bool trigger;

    Bounds bounds;
};

}
