
#include <iostream>
#include <cstring>
#include <glm/glm.hpp>

#include "../include/Board.hpp"
#include "../include/DefaultShader.hpp"
#include "../include/PrintPhysicsPosition.hpp"
#include "Components/Physic/RigidBody.hpp"
#include "Material.hpp"

using namespace std;
using namespace FerdiuEngine;


char *readMap(std::string mapFilePath, int &width, int &height)
{
    FILE *file;
    char buff[512];
    char current;
    int i = 0;
    file = fopen(mapFilePath.c_str(), "r");
    if (nullptr == file)
    {
        std::cerr << "error: couldn't read map file: " << mapFilePath << endl;
        exit(1);
    }
    for (i = 0; i < 511; i++)
    {
        current = (char) fgetc(file);

        if (current == '\n')
            break;
        else if (current == EOF)
        {
            std::cerr << "error: unexpected end of map file: " << mapFilePath << endl;
            exit(1);
        }

        buff[i] = current;
    }
    buff[i] = '\0';

    sscanf(buff, "%dx%d", &width, &height);

    char *map = (char*) malloc(sizeof(char) * width * height);
    i = 0;
    while((current = fgetc(file)) != EOF || i > width * height)
        if (current != '\n')
            map[i++] = current;

    fclose(file);
    return map;
}

// -----------------------------------------------------------------

Map::Map(string mapFilePath)
{
    this->data = readMap(mapFilePath, this->_width, this->_height);
}

int Map::width()
{
    return _width;
}
int Map::height()
{
    return _height;
}

char& Map::operator()(int i, int j)
{
    return data[i*(_width-1) + j];
}

char Map::operator()(int i, int j) const
{
    return data[i*(_width-1) + j];
}

void Map::print()
{
    int i, j;
    for (i = 0; i < this->_height; i++)
    {
        for (j = 0; j < this->_width; j++)
            std::cout << (*this)(i, j);
        std::cout << std::endl;
    }
}

// -----------------------------------------------------------------

Board::Board(string mapFilePath) : map(mapFilePath)
{
    this->root = new GameObject("BOARD");
    this->width = map.width();
    this->height = map.height();
}
Board::Board(string mapFilePath, Light *l) : Board(mapFilePath)
{
    this->l = l;
}

void Board::instantiate(GameObject *parent)
{
    this->root->instantiate(parent);
    build();
}
void Board::instantiate()
{
    instantiate(Scene::getCurrent()->root());
}
void Board::setLight(Light *l)
{
    this->l = l;

    // NOTE: really not efficient!!! but no time left...
    DefaultShader* ds;
    std::list<GameObject*>::iterator childIter;
    std::list<Component*>::iterator componentIter;
    for (childIter = root->getChildren().begin(); childIter != root->getChildren().end(); ++childIter)
        if ((*childIter)->isActive())
            for (componentIter = root->getComponents().begin(); componentIter != root->getComponents().end(); ++componentIter)
                if (nullptr != (ds = dynamic_cast<DefaultShader*>(*componentIter))) // is a DefaultShader
                    ds->setLight(l);
}

GameObject *Board::getRoot()
{
    return root;
}

void Board::addTilt(glm::vec2 v)
{
    _tilt += v;
    _tilt = glm::vec2(
        fmax(-1, fmin(_tilt[0], 1)),
        fmax(-1, fmin(_tilt[1], 1))
    );
    if (glm::length(_tilt) > 1)
        _tilt = glm::normalize(_tilt);
}
glm::vec2 Board::getTilt()
{
    return _tilt;
}

glm::vec3 Board::getStartPosition()
{
    return startPostion;
}

glm::vec3 Board::getStartPositionGlobal()
{
    return startPostion + root->getGlobalPosition();
}

// ---------------------------------------------------------------------------------

glm::vec2 Board::realPos(int i, int j)
{
    int halfW = width / 2;
    int halfH = height / 2;
    glm::vec2 r = glm::vec2(j - halfW, i - halfH);
    return r;
}

void Board::instantiateWall(int i, int j)
{
    GameObject *go = (new GameObject("WALL(" + std::to_string(i) + "x" + std::to_string(j) + ")"))
        ->addRigidbody(new RigidBody(RigidBody::RigidBodyType::RB_STATIC))
        ->addCollider(new BoxCollider(glm::vec3(1)))
        ->addRenderer(new CubeRenderer(1, *wood));
    go->instantiate(root);

    // TODO: remove this
    go->addComponent(new PrintPhysicsPosition());

    glm::vec2 xz = realPos(i, j);
    go->setLocalPosition(glm::vec3(xz[0], 0.5, xz[1]));

    DefaultShader *ds = new DefaultShader();
    ds->setColor(glm::vec4(0.84, 0.7, 0.61, 1));
    if (nullptr != l)
        ds->setLight(l);
    go->addComponent(ds);
}

void Board::instantiateStart(int i, int j)
{
    GameObject *go = (new GameObject("START(" + std::to_string(i) + "x" + std::to_string(j) + ")"))
        ->addRenderer(new SphereRenderer(0.5, *finish));
    go->instantiate(root);

    glm::vec2 xz = realPos(i, j);
    startPostion = glm::vec3(xz[0], 10, xz[1]);
    go->setLocalPosition(glm::vec3(xz[0], .5, xz[1]));

    DefaultShader *ds = new DefaultShader();
    ds->setColor(glm::vec4(1, 0, 0, .5));
    if (nullptr != l)
        ds->setLight(l);
    go->addComponent(ds);

}

void Board::instantiateFinish(int i, int j)
{
    GameObject *go = (new GameObject("FINISH(" + std::to_string(i) + "x" + std::to_string(j) + ")"))
        ->addRigidbody(new RigidBody(RigidBody::RigidBodyType::RB_STATIC))
        ->addCollider(new BoxCollider(glm::vec3(1)))
        ->addRenderer(new SphereRenderer(0.5, *finish));
    go->instantiate(root);

    // TODO: remove this
    go->addComponent(new PrintPhysicsPosition());

    glm::vec2 xz = realPos(i, j);
    go->setLocalPosition(glm::vec3(xz[0], 1, xz[1]));

    DefaultShader *ds = new DefaultShader();
    ds->setColor(glm::vec4(0, 1, 0, .5));
    if (nullptr != l)
        ds->setLight(l);
    go->addComponent(ds);

    go->collider().value()->setTrigger(true);
}

void Board::instantiateFloor(int i, int j)
{
    GameObject *go = (new GameObject("FLOOR(" + std::to_string(i) + "x" + std::to_string(j) + ")"))
        ->addRigidbody(new RigidBody(RigidBody::RigidBodyType::RB_STATIC))
        ->addCollider(new BoxCollider(glm::vec3(1)))
        ->addRenderer(new PlaneRenderer(1, *wood));
    go->instantiate(root);

    // TODO: remove this
    go->addComponent(new PrintPhysicsPosition());

    DefaultShader *ds = new DefaultShader();
    ds->setColor(glm::vec4(0.94, 0.8, 0.71, 1));
    if (nullptr != l)
        ds->setLight(l);
    // TODO: set default parameters
    go->addComponent(ds);

    glm::vec2 xz = realPos(i, j);
    go->setLocalPosition(glm::vec3(xz[0], 0, xz[1]));
}

void Board::instantiateHole(int i, int j)
{
    GameObject *go = (new GameObject("FINISH(" + std::to_string(i) + "x" + std::to_string(j) + ")"))
        ->addRigidbody(new RigidBody(RigidBody::RigidBodyType::RB_STATIC))
        ->addCollider(new BoxCollider(glm::vec3(1)));
    go->instantiate(root);

    // TODO: remove this
    go->addComponent(new PrintPhysicsPosition());

    glm::vec2 xz = realPos(i, j);
    go->setLocalPosition(glm::vec3(xz[0], -1, xz[1]));
    go->collider().value()->setTrigger(true);
}

void Board::build()
{
    int i, j;
    for (i = 0; i < this->height; i++)
        for (j = 0; j < this->width; j++)
            switch (map(i, j))
            {
                case ' ': instantiateFloor(i, j); break;
                case 'S': instantiateFloor(i, j); instantiateStart(i, j); break;
                case 'F': instantiateFloor(i, j); instantiateFinish(i, j); break;
                case '#': instantiateWall(i, j); break;
                case 'O': instantiateHole(i, j); break;
            }
}
