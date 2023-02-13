
#pragma once

#include <glm/glm.hpp>
#include "GLMatrices.hpp"

namespace FerdiuEngine
{

// Matrices stack node
typedef struct GLMatricesStackNode {
    GLMatrices *mat;
    struct GLMatricesStackNode *prev;
} GLMatricesStackNode;

// Matrices stack
typedef struct GLMatricesStack {
    GLMatricesStackNode *top;
} GLMatricesStack;


class MatricesStack
{
public:
    MatricesStack();
    ~MatricesStack();

    // matrices getters
    glm::mat4 *getPorjectionMatrix();
    glm::mat4 *getViewMatrix();
    glm::mat4 *getModelMatrix();

    // reset
    void reset();

    // stack operations
    void push();
    void pop();

    bool isEmpty();

private:
    GLMatricesStack *stack;

    void emptyStack();
    void createMatricesStack();
    void copyMatrix(glm::mat4 *dest, glm::mat4 *src);
    void copyMatrices(GLMatrices *dest, GLMatrices *src);
    GLMatricesStackNode *createNode(GLMatricesStackNode *prev = nullptr);
    void freeNode(GLMatricesStackNode *node);
};

}
