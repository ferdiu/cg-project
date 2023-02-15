
#pragma once

#include <glm/glm.hpp>
#include "GLMatrices.hpp"

#include "../FerdiuEngine_export.h"
#include "utils/Debug.hpp"

namespace FerdiuEngine
{

// Matrices stack node
typedef struct FERDIU_ENGINE_EXPORT GLMatricesStackNode {
    GLMatrices mat;
    struct GLMatricesStackNode *prev;
} GLMatricesStackNode;

// Matrices stack
typedef struct FERDIU_ENGINE_EXPORT GLMatricesStack {
    GLMatricesStackNode *top;
} GLMatricesStack;


class FERDIU_ENGINE_EXPORT MatricesStack
{
public:
    FERDIU_ENGINE_EXPORT MatricesStack();
    FERDIU_ENGINE_EXPORT ~MatricesStack();

    // matrices getters
    FERDIU_ENGINE_EXPORT glm::mat4 *getPorjectionMatrix();
    FERDIU_ENGINE_EXPORT glm::mat4 *getViewMatrix();
    FERDIU_ENGINE_EXPORT glm::mat4 *getModelMatrix();

    // matrices getters
    FERDIU_ENGINE_EXPORT void setPorjectionMatrix(glm::mat4 const& m);
    FERDIU_ENGINE_EXPORT void setViewMatrix(glm::mat4 const& m);
    FERDIU_ENGINE_EXPORT void setModelMatrix(glm::mat4 const& m);

    // reset
    FERDIU_ENGINE_EXPORT void reset();

    // stack operations
    FERDIU_ENGINE_EXPORT void push();
    FERDIU_ENGINE_EXPORT void pop();

    FERDIU_ENGINE_EXPORT bool isEmpty();

private:
    GLMatricesStack stack;

    void emptyStack();
    void createMatricesStack();
    GLMatricesStackNode *createNode(GLMatricesStackNode *prev = nullptr);
    void freeNode(GLMatricesStackNode *node);
};

}
