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
// human 1
// Humanoid *human = NULL;
// BodyParts *lArm = NULL;
// BodyParts *lHand = NULL;
// BodyParts *rArm = NULL;
// BodyParts *rHand = NULL;
// BodyParts *lThigh = NULL;
// BodyParts *lLeg = NULL;
// BodyParts *rThigh = NULL;
// BodyParts *rLeg = NULL;

// human 2
// Humanoid *human1 = NULL;
// BodyParts *lArm1 = NULL;
// BodyParts *lHand1 = NULL;
// BodyParts *rArm1 = NULL;
// BodyParts *rHand1 = NULL;
// BodyParts *lThigh1 = NULL;
// BodyParts *lLeg1 = NULL;
// BodyParts *rThigh1 = NULL;
// BodyParts *rLeg1 = NULL;

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

	// human textures
	// GLuint texture3 = LoadTexture("textures/boyf1.jpg"), texture4 = LoadTexture("textures/boyfb.jpg"), neckTex = LoadTexture("textures/neck.jpg");
	// GLuint texture5 = LoadTexture("textures/girlf1.jpg"), texture6 = LoadTexture("textures/girlfb.jpg"), pantTex = LoadTexture("textures/pant.jpg");
	// GLuint shirtTex = LoadTexture("textures/shirt.jpg");
	// GLuint weddingTex = LoadTexture("textures/wedding4.jpg");

	// human 1
	// cout << texture << texture1 << texture2 << "\n";
	// human = new Humanoid(glm::vec3(-(2.25*house->length+6*house->thickness) / 2.0, -house->height/8.0f+house->thickness*5.5f, -6*house->breadth/8.0f), shaderProgram.Program);
	// human->root->texture = shirtTex;
	// BodyParts *neck = new BodyParts(0.25f, 0.3f, 0.25f, human->root->center1 + glm::vec3(0.0f, (human->root->height / 2.0) + 0.1f, 0.0f), shaderProgram.Program, Neck, neckTex);
	// BodyParts *head = new BodyParts(0.5f, 0.55f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Head, -1);
	// BodyParts *headf = new BodyParts(0.5f, 0.005f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture3);
	// BodyParts *headb = new BodyParts(0.5f, 0.005f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture4);
	// BodyParts *headl = new BodyParts(0.01f, 0.55f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture4);
	// BodyParts *headr = new BodyParts(0.01f, 0.55f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture4);
	// BodyParts *headt = new BodyParts(0.5f, 0.55f, 0.005f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture4);
	// head->addBodyPart(headf, glm::vec3(0.0f, 0.0f, head->breadth / 2.0f - 0.001f));
	// head->addBodyPart(headb, glm::vec3(0.0f, 0.0f, -(head->breadth / 2.0f + 0.001f)));
	// head->addBodyPart(headl, glm::vec3(-(head->length / 2.0f + 0.001f), 0.0f, 0.0f));
	// head->addBodyPart(headr, glm::vec3((head->length / 2.0f + 0.001f), 0.0f, 0.0f));
	// head->addBodyPart(headt, glm::vec3(0.0f, (head->height / 2.0f + 0.001f), 0.0f));
	// neck->addBodyPart(head, glm::vec3(0.0f, 0.4f, 0.0f));
	// human->addBodyPart(neck, glm::vec3(0.0f));

	// lArm = new BodyParts(0.75f, 0.25f, 0.25f, human->root->center1 + glm::vec3(-human->root->length, human->root->breadth-0.2f, 0.0f), shaderProgram.Program, LeftArm, shirtTex);
	// lHand = new BodyParts(0.8f, 0.2f, 0.2f, glm::vec3(0.0f), shaderProgram.Program, LeftHand, neckTex);
	// lArm->addBodyPart(lHand, glm::vec3(-0.8f, 0.0f, 0.0f));
	// human->addBodyPart(lArm, glm::vec3(0.0f));

	// rArm = new BodyParts(0.75f, 0.25f, 0.25f, human->root->center1 + glm::vec3(human->root->length, human->root->breadth-0.2f, 0.0f), shaderProgram.Program, RightArm, shirtTex);
	// rHand = new BodyParts(0.8f, 0.2f, 0.2f, glm::vec3(0.0f), shaderProgram.Program, RightHand, neckTex);
	// rArm->addBodyPart(rHand, glm::vec3(0.8f, 0.0f, 0.0f));
	// human->addBodyPart(rArm, glm::vec3(0.0f));

	// lThigh = new BodyParts(0.35f, 0.45f, 0.85f, human->root->center1 + glm::vec3(-0.25f, -human->root->height+0.3f, 0.0f), shaderProgram.Program, LeftThigh, pantTex);
	// lLeg = new BodyParts(0.25f, 0.25f, 0.9f, glm::vec3(0.0f), shaderProgram.Program, LeftLeg, pantTex);
	// lThigh->addBodyPart(lLeg, glm::vec3(0.0f, -0.8f, 0.0f));
	// human->addBodyPart(lThigh, glm::vec3(0.0f));

	// rThigh = new BodyParts(0.35f, 0.45f, 0.85f, human->root->center1 + glm::vec3(0.25f, -human->root->height+0.3f, 0.0f), shaderProgram.Program, RightThigh, pantTex);
	// rLeg = new BodyParts(0.25f, 0.25f, 0.9f, glm::vec3(0.0f), shaderProgram.Program, RightLeg, pantTex);
	// rThigh->addBodyPart(rLeg, glm::vec3(0.0f, -0.8f, 0.0f));
	// human->addBodyPart(rThigh, glm::vec3(0.0f));

	// human 2
	// human1 = new Humanoid(glm::vec3(-(2.25*house->length - 8*house->thickness) / 2.0, -house->height/8.0f+house->thickness*5.5f, -6*house->breadth/8.0f), shaderProgram.Program);
	// human1->root->texture = weddingTex;
	// BodyParts *neck1 = new BodyParts(0.25f, 0.3f, 0.25f, human1->root->center1 + glm::vec3(0.0f, (human1->root->height / 2.0) + 0.1f, 0.0f), shaderProgram.Program, Neck, neckTex);
	// BodyParts *head1 = new BodyParts(0.5f, 0.55f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Head, -1);
	// BodyParts *headf1 = new BodyParts(0.5f, 0.005f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture5);
	// BodyParts *headb1 = new BodyParts(0.5f, 0.005f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture6);
	// BodyParts *headl1 = new BodyParts(0.005f, 0.55f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture6);
	// BodyParts *headr1 = new BodyParts(0.005f, 0.55f, 0.5f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture6);
	// BodyParts *headt1 = new BodyParts(0.5f, 0.55f, 0.005f, glm::vec3(0.0f), shaderProgram.Program, Plate, texture6);
	// head1->addBodyPart(headf1, glm::vec3(0.0f, 0.0f, head1->breadth / 2.0f - 0.001f));
	// head1->addBodyPart(headb1, glm::vec3(0.0f, 0.0f, -(head1->breadth / 2.0f + 0.001f)));
	// head1->addBodyPart(headl1, glm::vec3(-(head1->length / 2.0f + 0.001f), 0.0f, 0.0f));
	// head1->addBodyPart(headr1, glm::vec3((head1->length / 2.0f + 0.001f), 0.0f, 0.0f));
	// head1->addBodyPart(headt1, glm::vec3(0.0f, (head1->height / 2.0f + 0.001f), 0.0f));
	// neck1->addBodyPart(head1, glm::vec3(0.0f, 0.4f, 0.0f));
	// human1->addBodyPart(neck1, glm::vec3(0.0f));

	// lArm1 = new BodyParts(0.75f, 0.25f, 0.25f, human1->root->center1 + glm::vec3(-human1->root->length, human1->root->breadth-0.2f, 0.0f), shaderProgram.Program, LeftArm, neckTex);
	// lHand1 = new BodyParts(0.8f, 0.2f, 0.2f, glm::vec3(0.0f), shaderProgram.Program, LeftHand, neckTex);
	// lArm1->addBodyPart(lHand1, glm::vec3(-0.8f, 0.0f, 0.0f));
	// human1->addBodyPart(lArm1, glm::vec3(0.0f));

	// rArm1 = new BodyParts(0.75f, 0.25f, 0.25f, human1->root->center1 + glm::vec3(human1->root->length, human1->root->breadth-0.2f, 0.0f), shaderProgram.Program, RightArm, neckTex);
	// rHand1 = new BodyParts(0.8f, 0.2f, 0.2f, glm::vec3(0.0f), shaderProgram.Program, RightHand, neckTex);
	// rArm1->addBodyPart(rHand1, glm::vec3(0.8f, 0.0f, 0.0f));
	// human1->addBodyPart(rArm1, glm::vec3(0.0f));

	// lThigh1 = new BodyParts(0.35f, 0.45f, 0.85f, human1->root->center1 + glm::vec3(-0.25f, -human1->root->height+0.3f, 0.0f), shaderProgram.Program, LeftThigh, weddingTex);
	// lLeg1 = new BodyParts(0.25f, 0.25f, 0.9f, glm::vec3(0.0f), shaderProgram.Program, LeftLeg, neckTex);
	// lThigh1->addBodyPart(lLeg1, glm::vec3(0.0f, -0.8f, 0.0f));
	// human1->addBodyPart(lThigh1, glm::vec3(0.0f));

	// rThigh1 = new BodyParts(0.35f, 0.45f, 0.85f, human1->root->center1 + glm::vec3(0.25f, -human1->root->height+0.3f, 0.0f), shaderProgram.Program, RightThigh, weddingTex);
	// rLeg1 = new BodyParts(0.25f, 0.25f, 0.9f, glm::vec3(0.0f), shaderProgram.Program, RightLeg, neckTex);
	// rThigh1->addBodyPart(rLeg1, glm::vec3(0.0f, -0.8f, 0.0f));
	// human1->addBodyPart(rThigh1, glm::vec3(0.0f));

	// animation
	// for (int i = 0; i < 5; ++i)
	// {
	// 	lHand->swingHand(1);
	// 	lArm->swingHand(1);
	// 	rArm->swingHand(1);
	// 	rArm->swingHand(4);
	// }
	// for (int i = 0; i < 3; ++i)
	// {
	// 	lArm->swingHand(4);
	// 	lArm->swingHand(1);
	// 	rHand->swingHand(1);
	// }
	// rHand->swingHand(1);
	// for (int i = 0; i < 5; ++i)
	// {
	// 	lHand1->swingHand(1);
	// 	lArm1->swingHand(1);
	// 	rArm1->swingHand(1);
	// 	rArm1->swingHand(4);
	// }
	// for (int i = 0; i < 3; ++i)
	// {
	// 	lArm1->swingHand(4);
	// 	lArm1->swingHand(1);
	// 	rHand1->swingHand(1);
	// }
	// rHand1->swingHand(1);

	

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
		mbox1->createBox(glm::vec3(-(2.25*house->length - house->thickness) / 2.0, -house->height/8.0f+house->thickness*7.0f, -6*house->breadth/8.0f), shaderProgram.Program);
		// human->displayHumanoid();
		// human1->displayHumanoid();
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
		// 	if (human1->isDone) human1->rotCen();
		// 	if (human->isDone) human->rotCen();
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
