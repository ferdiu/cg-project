
#include <glm/glm.hpp>
#include <glm/gtx/functions.hpp>
#include <iostream>
#include <string>

#include "../../include/utils/Debug.hpp"
#include "../../include/utils/GLMatrices.hpp"
#include "../../include/utils/GLMatricesStack.hpp"

namespace FerdiuEngine
{

// ---------------------------- public --------------------------------------

MatricesStack::MatricesStack()
{
    createMatricesStack();
    reset();
}

MatricesStack::~MatricesStack()
{
    reset();
}

// matrices getters
glm::mat4 *MatricesStack::getPorjectionMatrix()
{
    return &(stack.top->mat.proj);
}
glm::mat4 *MatricesStack::getViewMatrix()
{
    return &(stack.top->mat.view);
}
glm::mat4 *MatricesStack::getModelMatrix()
{
    return &(stack.top->mat.model);
}

// matrices getters
void MatricesStack::setPorjectionMatrix(glm::mat4 const& m)
{
    copyMatrix(stack.top->mat.proj, m);
}
void MatricesStack::setViewMatrix(glm::mat4 const& m)
{
    copyMatrix(stack.top->mat.view, m);
}
void MatricesStack::setModelMatrix(glm::mat4 const& m)
{
    copyMatrix(stack.top->mat.model, m);
}


// reset
void MatricesStack::reset()
{
    emptyStack();
    stack.top = createNode();

    stack.top->mat.proj = glm::mat4(1.0);
    stack.top->mat.view = glm::mat4(1.0);
    stack.top->mat.model = glm::mat4(1.0);
}

// stack operations
void MatricesStack::push()
{
    GLMatricesStackNode *node = createNode(stack.top);
    copyMatrices(node->mat, stack.top->mat);
    stack.top = node;

}
void MatricesStack::pop()
{
#ifdef DEBUG
    if (isEmpty())
    {
        std::cerr << "warning: trying to pop empty GLMatricesStack" << std::endl;
        return;
    }
#endif
    GLMatricesStackNode *oldTop = stack.top;
    stack.top = oldTop->prev;
    freeNode(oldTop);
}

bool MatricesStack::isEmpty()
{
    return stack.top == nullptr;
}

// ---------------------------- private --------------------------------------

void MatricesStack::emptyStack()
{
    GLMatricesStackNode *node = stack.top;
    GLMatricesStackNode *tmp;
    while (node != nullptr)
    {
        tmp = node;
        node = node->prev;
        freeNode(tmp);
    }
}

void MatricesStack::createMatricesStack()
{
    stack.top = nullptr;
}

void MatricesStack::copyMatrix(glm::mat4& dest, glm::mat4 const& src)
{
    // NOTE: not sure this is the best way to do this
    // probably could have used memcpy for performances
    size_t i = 0, j = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            dest[i][j] = src[i][j];
}

void MatricesStack::copyMatrices(GLMatrices& dest, GLMatrices const& src)
{
    copyMatrix(dest.proj, src.proj);
    copyMatrix(dest.view, src.view);
    copyMatrix(dest.model, src.model);
}

GLMatricesStackNode *MatricesStack::createNode(GLMatricesStackNode *prev)
{
    GLMatricesStackNode *node = (GLMatricesStackNode *) malloc(sizeof(GLMatricesStackNode));
    node->prev = prev;
    return node;
}

void MatricesStack::freeNode(GLMatricesStackNode *node)
{
    node->prev = nullptr;
    free(node);
}

}
