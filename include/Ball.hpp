
#pragma once

#include <FerdiuEngine.hpp>

#include "Board.hpp"

class Ball : public FerdiuEngine::Component
{
public:
    Ball(Board *b);
    ~Ball() override;

    void awake() override;
    void fixedUpdate() override;

    void reset();

private:
    float velocityScale = 5;
    Board *b;
    FerdiuEngine::RigidBody *rb;
};
