#pragma once

#include "HalfEdgeDataStructure.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

Solid* mvsf(Point p, Vertex*& v);
HalfEdge* mev(Vertex* v, Point p, Loop* lp);
Loop* mef(Vertex* v1, Vertex* v2, Loop*& lp);
Loop* kemr(Vertex* v1, Vertex* v2, Loop*& lp);
void kfmrh(Loop* outterLp, Loop* innerLp);

Solid* sweep(Face* f, glm::vec3 dir, float dis);
