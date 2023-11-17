#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLEW_STATIC

using namespace std;

class Controller {
public:
    static bool InitC();
    static void Release();
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
    static void Movement(float deltaTime);

private:
    static bool keys[1024];

public:
    static float xAngle, yAngle, zAngle;
    static unsigned int count;
};

GLFWwindow* window;
const glm::ivec2 Screen_Size(720, 720);

int initEngine();
int Rendering();