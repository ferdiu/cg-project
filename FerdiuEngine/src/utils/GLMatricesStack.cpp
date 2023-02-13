
#include <glm/glm.hpp>
#include <iostream>
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
    free(stack);
}

// matrices getters
glm::mat4 *MatricesStack::getPorjectionMatrix()
{
    return &(stack->top->mat->proj);
}
glm::mat4 *MatricesStack::getViewMatrix()
{
    return &(stack->top->mat->view);
}
glm::mat4 *MatricesStack::getModelMatrix()
{
    return &(stack->top->mat->model);
}

// reset
void MatricesStack::reset()
{
    emptyStack();
    stack->top = createNode();

    stack->top->mat = (GLMatrices *) malloc(sizeof(GLMatrices));
    stack->top->mat->proj = glm::mat4(1.0);
    stack->top->mat->view = glm::mat4(1.0);
    stack->top->mat->model = glm::mat4(1.0);
}

// stack operations
void MatricesStack::push()
{
    // create a new node of the stack and copy mat in it
    GLMatricesStackNode *node = createNode(stack->top);

    stack->top = node;
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
    GLMatricesStackNode *oldTop = stack->top;

    if (oldTop != nullptr)
        stack->top = oldTop->prev;

    // copy removed node matrix to mat
    copyMatrices(stack->top->mat, oldTop->mat);

    freeNode(oldTop);
}

bool MatricesStack::isEmpty()
{
    return stack->top == nullptr;
}

// ---------------------------- private --------------------------------------

void MatricesStack::emptyStack()
{
    GLMatricesStackNode *node = stack->top;
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
    stack = (GLMatricesStack *) malloc(sizeof(GLMatricesStack));
    stack->top = nullptr;
}

void MatricesStack::copyMatrix(glm::mat4 *dest, glm::mat4 *src)
{
    // NOTE: not sure this is the best way to do this
    // probably could have used memcpy for performances
    size_t i = 0, j = 0;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            dest[i][j] = src[i][j];
}

void MatricesStack::copyMatrices(GLMatrices *dest, GLMatrices *src)
{
    copyMatrix(&(dest->proj), &(src->proj));
    copyMatrix(&(dest->view), &(src->view));
    copyMatrix(&(dest->model), &(src->model));
}

GLMatricesStackNode *MatricesStack::createNode(GLMatricesStackNode *prev)
{
    GLMatricesStackNode *node = (GLMatricesStackNode *) malloc(sizeof(GLMatricesStackNode));

    node->prev = prev;
    node->mat = (GLMatrices *) malloc(sizeof(GLMatrices));

    return node;
}

void MatricesStack::freeNode(GLMatricesStackNode *node)
{
    node->prev = nullptr;
    free(node->mat);
    free(node);
}

}
