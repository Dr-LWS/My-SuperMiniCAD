#pragma once

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class Solid;
class Face;
class Loop;
class HalfEdge;
class Edge;
class Vertex;
class Edge;
class Point;

class Vertex {
public:
	Vertex() :pre(nullptr), next(nullptr), point(nullptr) {}
	Vertex* pre, * next;
	Point* point;
};

class Edge {
public:
	Edge() :pre(nullptr), next(nullptr), leftHE(nullptr), rightHE(nullptr) {}
	Edge* pre, * next;
	HalfEdge* leftHE, * rightHE;
};

class HalfEdge {
public:
	HalfEdge() : edge(nullptr), lp(nullptr), pre(nullptr), next(nullptr), adjacent(nullptr), startV(nullptr), endV(nullptr) {}
	Edge* edge;
	Loop* lp;
	HalfEdge* pre, * next, * adjacent;
	Vertex* startV, * endV;
};

class Loop {
public:
	Loop() :face(nullptr), pre(nullptr), next(nullptr), halfedges(nullptr), innerlp(false) {}
	Face* face;
	Loop* pre, * next;
	HalfEdge* halfedges;
	int size();
	bool innerlp;
	bool isInnerLoop() const {
		return innerlp;
	}
	void setInner(bool signal) {
		innerlp = signal;
		return;
	}
};

class Face {
public:
	Face() : solid(nullptr), pre(nullptr), next(nullptr), lp(nullptr) {}
	Solid* solid;
	Face* pre, * next;
	Loop* lp;
	int size();
};

class Solid {
public:
	Solid() : pre(nullptr), next(nullptr), faces(nullptr), edges(nullptr) {}
	Solid* pre, * next;
	Face* faces;
	Edge* edges;
};

class Scene {
public:
	Solid* solidList;
};

class Point {
public:
	Point() :locate(0, 0, 0) {
		color = glm::vec3(0.88f, 0.42f, 0.59f);
	}
	glm::vec3 locate;
	glm::vec3 color;
	Point(double px, double py, double pz) :locate(px, py, pz) {}
	void SetP(double px, double py, double pz) {
		locate.x = px;
		locate.y = py;
		locate.z = pz;
	}
	void SetP(Point pt) {
		locate.x = pt.locate.x;
		locate.y = pt.locate.y;
		locate.z = pt.locate.z;
	}
};