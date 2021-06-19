#ifndef __INPUTDEVICE_H
#define __INPUTDEVICE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "Context.h"
#include<iostream>

class InputDeviceManager
{
    private:
        static GLboolean keys[1024];
        static Camera* camera;
        static GLfloat lastX, lastY;
        static GLboolean firstMouse;

        /**
         * last frame time
         */
        GLfloat lastFrame = 0.0f;

        /**
         * time between two frames
         */
        GLfloat deltaTime = 0.0f;

        /**
         * keyboard mapping
         */
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

        /**
         * mouse scroll
         */
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

        /**
         * handles mouse click
         */
        static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);

    public:
        InputDeviceManager(ContextManager* cm, Camera* camera);
        ~InputDeviceManager();

        /**
         * moves the camera
         */
        void updateCameraPosition();
};

#endif