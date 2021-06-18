#ifndef  __CONTEXT_H
#define __CONTEXT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>


class ContextManager
{
    private:
        // constants
        GLint height	= 600;
        GLint width 	= 800;
        
        GLFWwindow* window = 0;

    public:
    ContextManager();
    ~ContextManager();

    /**
     * initialize current context
     */
    void init();

    /**
     * sets param for current context
     */
    void setOptions();

    /**
     * returns current context
     */
    GLFWwindow* getContext();

    /**
     * returns height of current context
     */
    GLint getHeight();

    /**
     * returns width of current context
     */
    GLint getWidth();
};

#endif