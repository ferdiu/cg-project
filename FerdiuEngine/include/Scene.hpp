
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

    // current
    FERDIU_ENGINE_EXPORT static Scene *getCurrent();
    FERDIU_ENGINE_EXPORT void setCurrent();
    FERDIU_ENGINE_EXPORT static void setCurrent(Scene *scene);

    FERDIU_ENGINE_EXPORT GameObject *root();

    FERDIU_ENGINE_EXPORT void init();
    FERDIU_ENGINE_EXPORT void draw();

    FERDIU_ENGINE_EXPORT void update();
    FERDIU_ENGINE_EXPORT void fixedUpdate();
private:
    static Scene *current;

    std::string name = "";

    GameObject hierarchy = GameObject("ROOT");
};

}
