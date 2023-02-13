
#pragma once

#include <string>

namespace FerdiuEngine
{

class BitMapFile
{
public:
    // CONSTRUCTORS
    BitMapFile(char *filename);
    BitMapFile(std::string filename);
    ~BitMapFile();

    // GETTERS
    int width();
    int height();
    unsigned char *getData();

private:
    int sizeX;
    int sizeY;
    unsigned char *data;
};

}
