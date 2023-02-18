
#pragma once

#include <FerdiuEngine.hpp>

class Map
{
public:
    Map(std::string mapFilePath);
    char& operator()(int i, int j);
    char operator()(int i, int j) const;

    void print();
    int width();
    int height();

private:
    int _width;
    int _height;
    char *data;
};

class Board
{
public:
    Board(std::string mapFilePath);
    Board(std::string mapFilePath, FerdiuEngine::Light *l);

    void instantiate(FerdiuEngine::GameObject *parent);
    void instantiate();

    FerdiuEngine::GameObject *getRoot();

    void setLight(FerdiuEngine::Light *l);

    void addTilt(glm::vec2 v);
    glm::vec2 getTilt();

    glm::vec3 getStartPosition();
    glm::vec3 getStartPositionGlobal();

private:
    FerdiuEngine::GameObject *root = nullptr;
    glm::vec2 _tilt = glm::vec2(0);

    int width = 0;
    int height = 0;

    Map map;

    glm::vec3 startPostion = glm::vec3(0);

    FerdiuEngine::Light *l;

    FerdiuEngine::Shader *sh = new FerdiuEngine::Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    FerdiuEngine::Material *wood = new FerdiuEngine::Material(sh);
    FerdiuEngine::Material *finish = new FerdiuEngine::Material(sh);

    glm::vec2 realPos(int i, int j);
    void instantiateWall(int i, int j);
    void instantiateStart(int i, int j);
    void instantiateFinish(int i, int j);
    void instantiateFloor(int i, int j);
    void instantiateHole(int i, int j);
    void build();
};
