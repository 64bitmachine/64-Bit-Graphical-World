#include "include/inputdevice.h"

GLboolean InputDeviceManager::keys[1024];
Camera* InputDeviceManager::camera;
GLfloat InputDeviceManager::lastX;
GLfloat InputDeviceManager::lastY;
GLboolean InputDeviceManager::firstMouse = true;

InputDeviceManager::InputDeviceManager(ContextManager* cm, Camera* camera)
{
	this->camera = camera;
    glfwSetKeyCallback(cm->getContext(), key_callback);
	glfwSetScrollCallback(cm->getContext(), scroll_callback);
	glfwSetCursorPosCallback(cm->getContext(), mousePosCallback);
	glfwSetInputMode(cm->getContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	lastX = cm->getWidth() / 2.0;
	lastY = cm->getHeight() / 2.0;
}

InputDeviceManager::~InputDeviceManager()
{
}

void InputDeviceManager::updateCameraPosition()
{
    GLfloat currentFrame = glfwGetTime();
	GLfloat deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

    if (keys[GLFW_KEY_W])
		camera->ProcessKeyboard(FORWARD, deltaTime);
	
    if (keys[GLFW_KEY_S])
		camera->ProcessKeyboard(BACKWARD, deltaTime);
	
    if (keys[GLFW_KEY_A])
		camera->ProcessKeyboard(LEFT, deltaTime);
	
    if (keys[GLFW_KEY_D])
		camera->ProcessKeyboard(RIGHT, deltaTime);
	
    // if (keys[GLFW_KEY_Z]) 
	// 	camera.ProcessKeyboard(UP, deltaTime);
	
    // if (keys[GLFW_KEY_X]) 
	// 	camera.ProcessKeyboard(DOWN, deltaTime);
	
    // // rotate clock
    // if (keys[GLFW_KEY_Q])
	// 	camera.ProcessKeyboard(CLOCK, deltaTime);
	
    // // rotate anti
    // if (keys[GLFW_KEY_E])
	// 	camera.ProcessKeyboard(ANTI, deltaTime);
}

void InputDeviceManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
    // music box
	// if (key == GLFW_KEY_T && action == GLFW_PRESS)
	// {
	// 	mbox1->isOpen = GL_TRUE;
	// 	human->isshift = GL_TRUE;
	// 	human1->isshift = GL_TRUE;
	// }
	// if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	// {
	// 	mbox1->isOpen = GL_FALSE;
	// 	human->isshift = GL_FALSE;
	// 	human1->isshift = GL_FALSE;
	// }
	// if (key == GLFW_KEY_O && action == GLFW_PRESS)
	// {
	// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// }
	// if (key == GLFW_KEY_P && action == GLFW_PRESS)
	// {
	// 	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// }
	// if (key == GLFW_KEY_L && action == GLFW_PRESS)
	// {
	// 	isBeizer = !isBeizer;
	// }

	// if (key == GLFW_KEY_K && action == GLFW_PRESS)
	// {
	// 	int lights = 0, lamp = 0;
	// 	if(isLight.x>0.0f)
	// 		lights = 1;
	// 	if(isLight.y>0.0f)
	// 		lamp = 1;
	// 	cout <<lights<<" "<<lamp<<" "<<house->openWindow<<" "<<house->openDoor<<" "<<mbox1->openAngle<<" "<<human1->root->cen<<"\n";

	// 	outfile <<lights<<" "<<lamp<<" "<<house->openWindow<<" "<<house->openDoor<<" "<<mbox1->openAngle<<" "<<human1->root->cen<<"\n";
	// }
	// if (key == GLFW_KEY_J && action == GLFW_PRESS)
	// {
	// 	outfile.open ("keyframes.txt", ios::app);
	// }
	// if (key == GLFW_KEY_R && action == GLFW_PRESS)
	// {
	// 	recordMode = true;
	// 	infile.open("keyframes.txt");
	// }

	// open and closing sliding door
	// if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS)
	// 	house->isOpen = GL_TRUE;
	// if (key == GLFW_KEY_RIGHT_CONTROL && action == GLFW_PRESS)
	// 	house->isOpen = GL_FALSE;
	// // open and close door
	// if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
	// 	house->isOpen1 = GL_TRUE;
	// if (key == GLFW_KEY_RIGHT_SHIFT && action == GLFW_PRESS)
	// 	house->isOpen1 = GL_FALSE;

	// lights on/off
	// if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	// {
	// 	if (isLight.x > 0.0f) isLight.x=0.0f;
	// 	else isLight.x = 3.0f;
	// 	// cout << glm::to_string(isLight) << endl;
	// }
	// if (key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS)
	// {
	// 	if (isLight.y > 0.0f) isLight.y=0.0f;
	// 	else isLight.y = 3.0f;
	// 	// cout << glm::to_string(isLight) << endl;
	// }

	// if (key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS)
	// {	
	// 	int n = 4*800*600;
	// 	GLubyte pixels[n];// = new GLubyte[n];
	// 	glReadPixels(0,0,800,600, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	// 	int num_bytes_written = 0;
	// 	unsigned char ustore[n];// = new unsigned char[n];
	// 	for(unsigned int x=0; x<800; x++)
	// 		for(unsigned int y=0;y<600; y++)
	// 		{
	// 			unsigned int index=0, uindex=0;
	// 			index=(4*800*y) + (4*x);
	// 			uindex=(4*800*(600-y)) + (4*x);
	// 			ustore[uindex] = (unsigned char)(pixels[index]);
	// 			ustore[uindex+1]=(unsigned char)(pixels[index+1]);
	// 			ustore[uindex+2]=(unsigned char)(pixels[index+2]);
	// 			ustore[uindex+3]=(unsigned char)(pixels[index+3]);
	// 		}

	// 	time_t tt;
	//     // Applying time() 
	//     time (&tt); 
	//     // Using localtime() 
	//     tm TM  = *localtime(&tt);
	//     int year    = TM.tm_year + 1900;
	// 	int month   = TM.tm_mon ;
	// 	int day     = TM.tm_mday;
	// 	int hour    = TM.tm_hour;
	// 	int mins    = TM.tm_min ;
	// 	int secs    = TM.tm_sec ;

	// 	string temp = "screenshot/"+to_string(year)+to_string(month+1)+to_string(day)+to_string(hour)+to_string(mins)+to_string(secs)+".jpg";
	// 	num_bytes_written = stbi_write_jpg( temp.c_str(), 800, 600, 4, (void*)ustore, 90);
	    
	//     // cout << to_string(year)+to_string(month+1)+to_string(day)+to_string(hour)+to_string(mins)+to_string(secs)+".jpg" << endl;
	// }
	if (action == GLFW_PRESS)
		keys[key]=true;
	else if (action == GLFW_RELEASE)
		keys[key]=false;
}

void InputDeviceManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(yoffset);
}

void InputDeviceManager::mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	camera->ProcessMouseMovement(xpos - lastX, lastY - ypos);


	lastX = xpos;
	lastY = ypos;
}