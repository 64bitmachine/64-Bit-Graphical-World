#include <iostream>

#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#define STB_IMAGE_IMPLEMENTATION
// #define STBI_ONLY_TGA
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "include/Shader.h"
#include "include/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include "include/Mbox.h"
#include "include/texture.hpp"
#include "include/Humanoid.h"
#include "include/House.h"
#include <ctime>
#include <fstream>
#include <vector>
#include "include/Context.h"
#include "include/preprocessing.h"
#include "include/inputdevice.h"

using namespace std;

// bool keys[1024];

// GLint activeHuman = 0;
House *house=NULL;

GLint PointShader;

// GLboolean isBeizer = GL_FALSE;

// cube
GLuint cubeVAO, cubeVBO;

// line
GLuint lineVAO, lineVBO;

// time between two frames
// GLfloat lastFrame = 0.0f;	// last frame time

GLfloat lastX = 400, lastY = 300;
// GLfloat deltaTime = 0.0f;
GLboolean firstMouse = true;
glm::vec3 isLight = glm::vec3(3.0f);
glm::vec3 isLight1 = glm::vec3(3.0f);

// vector<glm::vec3> pathlist;

Camera camera(glm::vec3(0.0f, 33.0f, 70.0f));
Mbox *mbox1 = NULL, *mbox2 = NULL;

glm::mat4 projection = glm::mat4(1.0f);
glm::mat4 view;// = glm::mat4(1.0f)

ofstream outfile;
ifstream infile;

GLboolean recordMode = false;

void drawCube()
{
	GLfloat vertices[108] = {
		-0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f, 
		-0.5f,  0.5f, -0.5f, 

		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		0.5f,  0.5f,  0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 

		-0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f, -0.5f, 

		-0.5f,  0.5f, -0.5f,  
		0.5f,  0.5f,  0.5f,  
		0.5f,  0.5f, -0.5f,  
		0.5f,  0.5f,  0.5f,  
		-0.5f,  0.5f, -0.5f,  
		-0.5f,  0.5f,  0.5f
	};
	glGenBuffers(1, &cubeVBO);
	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void renderCube(glm::vec3 center)
{
	glUniformMatrix4fv(glGetUniformLocation(PointShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(PointShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, center);
	model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
	glUniformMatrix4fv(glGetUniformLocation(PointShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

GLfloat data[300];

void renderLine()
{
	glUniformMatrix4fv(glGetUniformLocation(PointShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(PointShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glm::mat4 model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(PointShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(lineVAO);
	glDrawArrays(GL_LINE_STRIP, 0, 100);
	glBindVertexArray(0);
}

// void drawPoints()
// {
// 	for (int i = 0; i < pathlist.size(); ++i)
// 	{
// 		renderCube(glm::vec3(pathlist[i].x,pathlist[i].y,pathlist[i].z));
// 	}
// 	if (pathlist.size()==4)
// 	{
// 		int pointCount = 0;
// 		GLfloat vertices1[12];
// 		while (pointCount < pathlist.size())
// 		{
// 			int count = 0;
// 			for (int j = 0; j < 12; j++)
// 			{
// 				vertices1[j++] = (pathlist[pointCount].x);
// 				vertices1[j++] = (pathlist[pointCount].y);
// 				vertices1[j] = (pathlist[pointCount].z);
// 				pointCount++;
// 			}
// 			for (float a = 0; a < 1.0f; a += (0.01f)) {
// 				data[count++] = (1 - a)*(1 - a)*(1 - a)*vertices1[0] + 3 * a*(1 - a)*(1 - a)*vertices1[3] + 3 * a*a*(1 - a)*vertices1[6] + a * a*a*vertices1[9];
// 				data[count++] = (1 - a)*(1 - a)*(1 - a)*vertices1[1] + 3 * a*(1 - a)*(1 - a)*vertices1[4] + 3 * a*a*(1 - a)*vertices1[7] + a * a*a*vertices1[10];
// 				data[count++] = (1 - a)*(1 - a)*(1 - a)*vertices1[2] + 3 * a*(1 - a)*(1 - a)*vertices1[5] + 3 * a*a*(1 - a)*vertices1[8] + a * a*a*vertices1[11];	
// 			}
// 			glGenBuffers(1, &lineVBO);
// 			glGenVertexArrays(1, &lineVAO);
// 			glBindVertexArray(lineVAO);
// 			glBindBuffer(GL_ARRAY_BUFFER, lineVBO);
// 			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
// 			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
// 			glEnableVertexAttribArray(0);
// 			glBindBuffer(GL_ARRAY_BUFFER, 0);
// 			glBindVertexArray(0);
// 		}
// 		renderLine();
// 	}
// }

void initCallBacks(ContextManager* cm)
{
	GLFWwindow* window = cm->getContext();
	
	// glfwSetMouseButtonCallback(window, mousebutton_callback);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}



int main() 
{

	ContextManager cm;
	cm.init();

	initGLEW();
	initCallBacks(&cm);

	printGraphicsDetails();
	glViewport(0, 0, cm.getWidth(), cm.getHeight());

	InputDeviceManager idm(&cm, &camera);

	// setup opengl options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);

	mbox1 = new Mbox();

	// land texture
	GLuint landTex = LoadTexture("textures/grass1.jpg");
	GLuint wallTex = LoadTexture("textures/wal.jpg");
	GLuint windowTex = LoadTexture("textures/blending_transparent_window.png", GL_TRUE);
	GLuint roofTex = LoadTexture("textures/roof1.jpg");

	Shader shaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
	Shader pointShader("shaders/pvertex.glsl", "shaders/pfragment.glsl");
	PointShader = pointShader.Program;
	Shader lampProgram("shaders/lvertex.glsl", "shaders/lfragment.glsl");
	Shader lampProgram1("shaders/lvertex.glsl", "shaders/lfragment1.glsl");

	GLuint texture = LoadTexture("textures/te.jpg");
	GLuint texture1 = LoadTexture("textures/test.bmp");
	GLuint velvet = LoadTexture("textures/velvet.jpg");
	GLuint woodTex = LoadTexture("textures/wood.jpeg");
	


	// house
	house = new House();
	house->floorTex = landTex;
	house->wallTex = wallTex;
	house->windowTex = windowTex;
	house->roofTex = roofTex;
	house->wood = woodTex;
	house->sofa = velvet;

	mbox1->texture = texture1;
	mbox1->texture1 = texture;
	mbox1->texture2 = velvet;
	mbox1->innerTex = woodTex;

	// cout << texture << texture1 << texture2 << "\n";
	Humanoid *romeo = new Humanoid(glm::vec3(-(2.25*house->length+6*house->thickness) / 2.0, -house->height/8.0f+house->thickness*5.5f, 
							-6*house->breadth/8.0f), shaderProgram.Program, 'M');



	Humanoid *juliet = new Humanoid(glm::vec3(-(2.25*house->length - 8*house->thickness) / 2.0, -house->height/8.0f+house->thickness*5.5f,
							-6*house->breadth/8.0f), shaderProgram.Program, 'F');

	
	GLint count = 0, count1=0, count2=0;

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.0f,  15.2f,  0.0f),
		glm::vec3(-house->length, 15.2f, -house->breadth / 2.0f),
		glm::vec3(-house->length/2.0f, (house->height-house->thickness)/2.0f-house->length/10.0f, -house->breadth + house->thickness*10)
	};

	// glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	// pointShader.Use();
	// glUniform3fv(glGetUniformLocation(pointShader.Program, "vertexColor"), 1, &color[0]);
	// drawCube();

	while (!glfwWindowShouldClose(cm.getContext())) {
		
		glfwPollEvents();
		idm.updateCameraPosition();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		 view = camera.GetViewMatrix();

		//;
		projection = glm::perspective(glm::radians(camera.getZoom()), 800.0f / 600.0f, 0.1f, 300.0f);

		lampProgram.Use();
		glUniformMatrix4fv(glGetUniformLocation(lampProgram.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lampProgram.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(glGetUniformLocation(lampProgram.Program, "isLight"), isLight.x, isLight.y, isLight.z);
		house->createLight(lampProgram.Program);
		lampProgram1.Use();
		glUniformMatrix4fv(glGetUniformLocation(lampProgram1.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(lampProgram1.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3f(glGetUniformLocation(lampProgram1.Program, "isLight"), isLight.x, isLight.y, isLight.z);
		house->createLight1(lampProgram1.Program);

		shaderProgram.Use();
		glUniform3f(glGetUniformLocation(shaderProgram.Program, "viewPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		glUniform3f(glGetUniformLocation(shaderProgram.Program, "isLight"), isLight.x, isLight.y, isLight.z);
		// Set lights properties
		// Directional light
		glUniform3f(glGetUniformLocation(shaderProgram.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(shaderProgram.Program, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
		glUniform3f(glGetUniformLocation(shaderProgram.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(shaderProgram.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
		if (isLight.x > 0.0f)
		{
			// Point light 1
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].diffuse"), 50.8f, 50.8f, 50.8f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].linear"), 0.09);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].quadratic"), 0.032);
			// Point light 2
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].diffuse"), 50.8f, 50.8f, 50.8f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].linear"), 0.09);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].quadratic"), 0.032);
		}
		else 
		{
			// Point light 1
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].linear"), 0.09);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[0].quadratic"), 0.032);
			// Point light 2
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].linear"), 0.09);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[1].quadratic"), 0.032);
		}
		// lamp light
		if (isLight.y > 0.0f)
		{
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].ambient"), 0.05f, 0.09f, 0.1f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].diffuse"), 5.1f, 9.0f, 10.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].linear"), 0.09);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].quadratic"), 0.032);
		}
		else
		{
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].ambient"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].diffuse"), 0.0f, 0.0f, 0.0f);
			glUniform3f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].constant"), 1.0f);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].linear"), 0.09);
			glUniform1f(glGetUniformLocation(shaderProgram.Program, "pointLights[2].quadratic"), 0.032);
		}

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniform1i(glGetUniformLocation(shaderProgram.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram.Program, "material.specular"), 1);
		glUniform1f(glGetUniformLocation(shaderProgram.Program, "material.shininess"), 32.0f);
		// mbox1->createBox(glm::vec3(-(2.25*house->length - house->thickness) / 2.0, -house->height/8.0f+house->thickness*7.0f, -6*house->breadth/8.0f), shaderProgram.Program);
		romeo->visible();
		juliet->visible();
		house->createHouse(glm::vec3(0.0f), shaderProgram.Program);
		count++;
		count1++;
		// if (count1%2==0 && pathlist.size()==4 && isBeizer) 
		// {
		// 	count1=0;
		// 	camera.setFront(-glm::vec3(camera.getPosition().x+(2.25*house->length - house->thickness) / 2.0, 
		// 		camera.getPosition().y+house->height/8.0f-house->thickness*7.0f, 
		// 		camera.getPosition().z+6*house->breadth/8.0f));
		// 	camera.setPosition(glm::vec3(data[3*count2], data[3*count2+1], data[3*count2+2]));
		// 	count2++;
		// 	if(count2%100==0)
		// 	{
		// 		count2=0;
		// 		isBeizer=GL_FALSE;
		// 	}
		// }
		// if (count == 5) 
		// {
		// 	count = 0;
		// 	if (juliet->isDone) juliet->rotCen();
		// 	if (romeo->isDone) romeo->rotCen();
		// }

		// pointShader.Use();
		// if (pathlist.size()) 
		// {
		// 	drawPoints();
		// }

		glfwSwapBuffers(cm.getContext());
	}

	glfwTerminate();
	return 0;
}
