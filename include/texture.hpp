#include <iostream>
#include <GL/glew.h>
#include "stb/stb_image.h"

GLuint LoadTexture( const char * filename, GLboolean alpha = GL_FALSE);
void FreeTexture( GLuint texture );