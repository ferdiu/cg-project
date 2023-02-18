
#pragma once

#include <FerdiuEngine.hpp>
#include <glm/glm.hpp>

class LookAtCamera : public FerdiuEngine::Component
{
public:
    LookAtCamera(FerdiuEngine::GameObject *target, FerdiuEngine::Camera *c = nullptr, glm::vec3 up = glm::vec3(0, 1, 0));
    LookAtCamera(FerdiuEngine::Transform *target, FerdiuEngine::Camera *c = nullptr, glm::vec3 up = glm::vec3(0, 1, 0));
    ~LookAtCamera() override;

    void awake() override;
    void update() override;

    // TODO: void changeTarget(FerdiuEngine::GameObject *target);
    // TODO: void changeTarget(FerdiuEngine::Transform *target);
    // TODO: FerdiuEngine::Transform *getTarget();
    // TODO: void changeCamera();
    // TODO: FerdiuEngine::Camera void getCamera();
    // TODO: void changeUp();
    // TODO: glm::vec3 getUp() const;

private:
    FerdiuEngine::Transform *target;
    FerdiuEngine::Camera *camera;
    glm::vec3 up;
};

