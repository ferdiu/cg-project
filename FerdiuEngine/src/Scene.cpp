
#include <iostream>
#include <string>

#include "../include/Scene.hpp"
#include "../include/GameObject.hpp"

namespace FerdiuEngine
{

Scene::Scene(::std::string name)
{
    this->name = name;
    hierarchy.setScene(this);
}

Scene *Scene::getCurrent()
{
    return current;
}

void Scene::setCurrent()
{
    Scene::setCurrent(this);
}

void Scene::setCurrent(Scene *scene)
{
    if (scene != current)
        scene->init();

    current = scene;
}

GameObject *Scene::root()
{
    return &hierarchy;
}

void Scene::init()
{
    this->hierarchy.awake();
}

void Scene::update()
{
    this->hierarchy.update();
}
void Scene::fixedUpdate()
{
    this->hierarchy.fixedUpdate();
}

void Scene::draw()
{
    hierarchy.draw();
}

Scene *Scene::current = new Scene("_");

}
