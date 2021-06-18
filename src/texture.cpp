
// #include <fstream>
// #include <cstdlib>
#include "include/texture.hpp"

GLuint LoadTexture( const char * filename, GLboolean alpha)
{
    GLuint texture;
 //    unsigned char header[54];// 54 Byte header of BMP
 //    int pos;
 //    unsigned int w,h;
 //    unsigned int size; //w*h*3
 //    unsigned char * data; // Data in RGB FORMAT
 //    FILE * file;
    
 //    file = fopen( filename, "rb" ); 
 //    if ( file == NULL ) return 0;  // if file is empty 
 //    if (fread(header,1,54,file)!=54)
 //      {
	// printf("Incorrect BMP file\n");
	// return 0;
 //      }

 //    // Read  MetaData
 //    pos = *(int*)&(header[0x0A]);
 //    size = *(int*)&(header[0x22]);
 //    w = *(int*)&(header[0x12]);
 //    h = *(int*)&(header[0x16]);

 //    //Just in case metadata is missing
 //    if(size == 0) 
 //      size = w*h*3;
 //    if(pos == 0)
 //      pos = 54;

 //    data = new unsigned char [size];

 //    fread( data, size, 1, file ); // read the file
 //    fclose( file );
 //    //////////////////////////

 //    glGenTextures( 1, &texture );
 //    glBindTexture( GL_TEXTURE_2D, texture );
   

 //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
 //    free( data );

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 
     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, alpha ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, alpha ? GL_RGBA : GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    return texture;// return the texture id
}
void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture ); // delete the texture
}
