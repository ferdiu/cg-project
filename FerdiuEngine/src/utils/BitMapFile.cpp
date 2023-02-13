
#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/gl.h>
#include "../../include/utils/BitMapFile.hpp"

namespace FerdiuEngine
{

// CONSTRUCTORS
BitMapFile::BitMapFile(char *filename)
{
    GLint offset, headerSize;
    GLuint padding, sizeScanline, sizeStorage;
    int startScanline, endScanlineImageData, temp, x, y, nread;
    FILE *infile;
    BitMapFile *bmpRGB;

    // Initialize bitmap files for RGB (input) and RGBA (output).
    bmpRGB = (BitMapFile *) malloc(sizeof(BitMapFile));

    // Read input bmp file name
    infile = fopen(filename, "rb");
    if (infile == NULL)
        fprintf(stderr, "warning: texture file \"%s\" not found\n", filename);

    // get data offset
    fseek(infile, 10, SEEK_SET);
    // get offset and header size
    nread = fread(&offset, 4, 1, infile);
    if (nread <= 0) perror("fread");
    nread = fread(&headerSize, 4, 1, infile);
    if (nread <= 0) perror("fread");

    // get image width and height
    fseek(infile, 18, SEEK_SET);
    nread = fread((GLubyte *)&bmpRGB->sizeX, 4, 1, infile);
    if (nread <= 0) perror("fread");
    nread = fread((GLubyte *)&bmpRGB->sizeY, 4, 1, infile);
    if (nread <= 0) perror("fread");

    // Determine the length of zero-byte padding of the scanlines
    // (each scanline of a bmp file is 4-byte aligned by padding with zeros).
    padding = (3 * bmpRGB->sizeX) % 4 ? 4 - (3 * bmpRGB->sizeX) % 4 : 0;

    // Add the padding to determine size of each scanline.
    sizeScanline = 3 * bmpRGB->sizeX + padding;

    // Allocate storage for image in input bitmap file.
    sizeStorage = sizeScanline * bmpRGB->sizeY;
    bmpRGB->data = (unsigned char *) malloc(sizeStorage);

    // Read bmp file image data into input bitmap file.
    fseek(infile, offset, SEEK_SET);
    nread = fread((unsigned char *) bmpRGB->data, 1, sizeStorage, infile);
    if (nread <= 0) perror("fread");

    // close image file
    fclose(infile);

    // Reverse color values from BGR (bmp storage format) to RGB.
    for (y = 0; y < bmpRGB->sizeY; y++) {
        startScanline = y * sizeScanline; // Start position of y'th scanline.
        endScanlineImageData = startScanline + 3 * bmpRGB->sizeX; // Image data excludes padding.
        for (x = startScanline; x < endScanlineImageData; x += 3) {
            temp = bmpRGB->data[x];
            bmpRGB->data[x] = bmpRGB->data[x + 2];
            bmpRGB->data[x + 2] = temp;
        }
    }

    // Set image width and height values and allocate storage for image in output bitmap file.
    this->sizeX = bmpRGB->sizeX;
    this->sizeY = bmpRGB->sizeY;
    this->data = (unsigned char *) malloc(4 * bmpRGB->sizeX * bmpRGB->sizeY);

    // Copy RGB data from input to output bitmap files, set output A to 1.
    for (x = 0; x < 4 * bmpRGB->sizeY * bmpRGB->sizeX; x += 4) {
        this->data[x] = bmpRGB->data[(x / 4) * 3];
        this->data[x + 1] = bmpRGB->data[(x / 4) * 3 + 1];
        this->data[x + 2] = bmpRGB->data[(x / 4) * 3 + 2];
        this->data[x + 3] = 0xFF;
    }

    // free temporary memory
    free(bmpRGB->data);
    free(bmpRGB);
}

BitMapFile::BitMapFile(std::string filename) : BitMapFile::BitMapFile((char *) filename.c_str()) {}

BitMapFile::~BitMapFile()
{
    free(this->data);
}

// GETTERS
int BitMapFile::width()
{
    return sizeX;
}
int BitMapFile::height()
{
    return sizeY;
}
unsigned char *BitMapFile::getData()
{
    return data;
}

}
