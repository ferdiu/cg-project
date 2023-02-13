
#pragma once

#include <glm/glm.hpp>
#include "../Component.hpp"

namespace FerdiuEngine
{

class Bounds
{
public:
    Bounds(glm::vec3 center = glm::vec3(0), glm::vec3 size = glm::vec3(1));

    glm::vec3 getCenter();
    glm::vec3 getSize();

    glm::vec3 getExtents();
    glm::vec3 getMin();
    glm::vec3 getMax();

protected:
    virtual void setCenter(glm::vec3 v);
    virtual void setSize(glm::vec3 v);

    void setExtentes(glm::vec3 v);
    void setMin(glm::vec3 v);
    void setMax(glm::vec3 v);

private:
    glm::vec3 center = glm::vec3(0, 0, 0);
    glm::vec3 size = glm::vec3(1, 1, 1);

    glm::vec3 extents;
    glm::vec3 min;
    glm::vec3 max;
};

}
