#include "main.hpp"
#include "testObject.h"
#include <iostream>
#include <algorithm>

using namespace std;
using namespace glm;

float Controller::xAngle = 0.0;
float Controller::yAngle = 0.0;
float Controller::zAngle = 0.0;
unsigned int Controller::count = 0;
bool Controller::keys[1024] = { false };

int main() {

	// Initialization
	initEngine();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.51f, 0.80f, 0.67f, 1.0f);

    Rendering();
    return 0;
}

int initEngine() {

	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(Screen_Size.x, Screen_Size.y, "miniCAD", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

    if (!Controller::InitC())
    {
        std::cout << "Unable to initialize camera!" << endl;
    }

    glfwSetKeyCallback(window, Controller::KeyCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    std::cout << "===============================" << endl;
    std::cout << "   Successfully Initialized£¡" << endl;
    std::cout << "===============================" << endl << endl;

    return 0;
}

int Rendering() {
    std::cout << "        Now Rendering..." << endl;

    vector<Solid*> solidList;
    Solid* S0 = CreateCube();
    solidList.push_back(S0);
    Solid* S1 = CreateTunnel();
    solidList.push_back(S1);
    Solid* S2 = CreatePyramid();
    solidList.push_back(S2);

    GLfloat deltaTime = 0, currentTime = 0;
    GLfloat startTime = glfwGetTime();
    GLfloat lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        Solid* drawSolid = solidList[Controller::count % solidList.size()];
        glfwPollEvents();
        GLfloat newTime = glfwGetTime();
        Controller::Movement(newTime - lastTime);
        lastTime = newTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, Screen_Size.x, Screen_Size.y);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f, Screen_Size.x / Screen_Size.y, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity(); 
        glTranslatef(0.0f, 0.0f, -10.0f);

        glRotatef(Controller::xAngle, 1.0f, 0.0f, 0.0f);
        glRotatef(Controller::yAngle, 0.0f, 1.0f, 0.0f);
        glRotatef(Controller::zAngle, 0.0f, 0.0f, 1.0f);

        glRotatef(180.0, 0.0f, 1.0f, 0.0f);
        glRotatef(90.0, 1.0f, 0.0f, 0.0f);

        DrawSolid(drawSolid);

        glfwSwapBuffers(window);
    }

    Controller::Release();

    glfwTerminate();
    return 0;
}

bool Controller::InitC()
{
    return true;
}

void Controller::Release()
{
}

void Controller::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS) {
        count++;
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void Controller::Movement(float deltaTime)
{
    deltaTime *= 50;

    if (keys[GLFW_KEY_W])
        xAngle += 1.0f * deltaTime;
    if (keys[GLFW_KEY_S])
        xAngle -= 1.0f * deltaTime;
    if (keys[GLFW_KEY_A])
        yAngle += 1.0f * deltaTime;
    if (keys[GLFW_KEY_D])
        yAngle -= 1.0f * deltaTime;
    if (keys[GLFW_KEY_Q])
        zAngle += 1.0f * deltaTime;
    if (keys[GLFW_KEY_E])
        zAngle -= 1.0f * deltaTime;
}
