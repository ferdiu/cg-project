
#pragma once

#include <FerdiuEngine.hpp>

#include "Board.hpp"

class Ball : public FerdiuEngine::Component
{
public:
    Ball(Board *b);
    ~Ball() override;

    void start() override;
    void fixedUpdate() override;

    void reset();

private:
    float velocityScale = 50;
    Board *b;
    FerdiuEngine::RigidBody *rb;
};
