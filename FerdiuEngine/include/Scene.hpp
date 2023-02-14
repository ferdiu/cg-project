
#pragma once

#include <iostream>
#include <string>

#include "GameObject.hpp"

#include "FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT Scene
{
public:
    FERDIU_ENGINE_EXPORT Scene(std::string name);

private:
    std::string name = "";

    GameObject hierarchy = GameObject();
};

}
