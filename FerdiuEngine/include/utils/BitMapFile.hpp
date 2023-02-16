
#pragma once

#include <string>

#include "../FerdiuEngine_export.h"

namespace FerdiuEngine
{

class FERDIU_ENGINE_EXPORT BitMapFile
{
public:
    // CONSTRUCTORS
    FERDIU_ENGINE_EXPORT BitMapFile(char *filename);
    FERDIU_ENGINE_EXPORT BitMapFile(std::string filename);
    FERDIU_ENGINE_EXPORT ~BitMapFile();

    // GETTERS
    FERDIU_ENGINE_EXPORT int width();
    FERDIU_ENGINE_EXPORT int height();
    FERDIU_ENGINE_EXPORT unsigned char *getData();
    FERDIU_ENGINE_EXPORT unsigned char& getData() const;

private:
    int sizeX;
    int sizeY;
    unsigned char *data;
};

}
