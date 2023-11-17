#pragma once

#include "HalfEdgeDataStructure.h"
#include "EulerOperation.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

using namespace std;

struct TessData
{
    GLdouble data[6];
    TessData(glm::vec3 point, glm::vec3 color)
    {
        data[0] = point.x;
        data[1] = point.y;
        data[2] = point.z;
        data[3] = color.r;
        data[4] = color.g;
        data[5] = color.b;
    }
};

void DrawSolid(Solid* s);
void DrawFace(Face* f);
void Drawing(Loop* lp);

void CALLBACK tessBeginCB(GLenum which);
void CALLBACK tessEndCB();
void CALLBACK tessVertexCB(const GLvoid* data);