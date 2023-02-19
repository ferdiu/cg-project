
#pragma once

#include <FerdiuEngine.hpp>

class PrintPhysicsPosition : public FerdiuEngine::Component
{
public:
    void awake() override;
    void fixedUpdate() override;

private:
    FerdiuEngine::RigidBody *rb;
    std::string name;
};
