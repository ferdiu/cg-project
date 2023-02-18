
#pragma once

#include <FerdiuEngine.hpp>

#include "Board.hpp"

class Ball : public FerdiuEngine::Component
{
public:
    Ball(Board *b);
    ~Ball() override;

    void awake() override;
    void update() override;

    void reset();

private:
    float velocityScale = 2;
    Board *b;
    FerdiuEngine::RigidBody *rb;
};
