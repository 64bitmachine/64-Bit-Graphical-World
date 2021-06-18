#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

#include <GL/glew.h>	// include glew to get all required opengl

class Shader
{
public:
	// the program id
	GLint Program;

	// construct reads and build the shader
	Shader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);

	// use the program
	void Use();
};
#endif
