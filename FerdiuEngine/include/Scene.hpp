
#pragma once

#include <iostream>
#include <string>

#include "GameObject.hpp"

namespace FerdiuEngine
{

class Scene
{
public:
    Scene(std::string name);

private:
    std::string name = "";

    GameObject hierarchy = GameObject();
};

}
