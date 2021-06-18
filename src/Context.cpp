#include "include/Context.h"

ContextManager::ContextManager()
{
}

ContextManager::~ContextManager()
{
}

void ContextManager::init()
{
    glfwInit();
    setOptions();

    // creating a context
	window = glfwCreateWindow(width, height, "shader", nullptr, nullptr);
    if (window == nullptr) {
		std::cout << "failed to create glfw window\n";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
}

void ContextManager::setOptions()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
}

GLFWwindow* ContextManager::getContext()
{
    return window;
}

GLint ContextManager::getHeight()
{
	return height;
}

GLint ContextManager::getWidth()
{
	return width;
}