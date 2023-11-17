#include "Drawing.h"

using namespace std;

void Drawing(Loop* lp) {
	GLuint id = glGenLists(1);
	if (!id) return;

	GLUtesselator* tess = gluNewTess();
	if (!tess) return;

	gluTessCallback(tess, GLU_TESS_BEGIN, (void(CALLBACK*)())tessBeginCB);
	gluTessCallback(tess, GLU_TESS_END, (void(CALLBACK*)())tessEndCB);
	gluTessCallback(tess, GLU_TESS_VERTEX, (void(CALLBACK*)())tessVertexCB);

	glNewList(id, GL_COMPILE);
	glColor3f(1, 1, 1);
	gluTessBeginPolygon(tess, 0);
	gluTessBeginContour(tess);

	HalfEdge* startHE = lp->halfedges;
	HalfEdge* HE = lp->halfedges;
	Vertex* startV = HE->startV;
	vector<TessData> quadList;
	do {
		glm::vec3 point = HE->startV->point->locate;
		glm::vec3 color = HE->startV->point->color;
		TessData data(point, color);
		quadList.push_back(data);
		HE = HE->next;
	} while (HE != nullptr && HE != startHE);

	for (int i = 0; i < quadList.size(); i++) {
		gluTessVertex(tess, quadList[i].data, quadList[i].data);
	}

	gluTessEndContour(tess);
	gluTessEndPolygon(tess);
	glEndList();
	
	gluDeleteTess(tess);
	glCallList(id);

	glLineWidth(2.0f);
	glBegin(GL_LINE_LOOP);

	HalfEdge* startH = lp->halfedges;
	HE = lp->halfedges;
	startV = HE->startV;

	do {
		glm::vec3 point = HE->startV->point->locate;
		glm::vec3 color = HE->startV->point->color;
		glColor3f(0, 0, 0);
		glVertex3f(point.x, point.y, point.z);
		HE = HE->next;
	} while (HE != nullptr && HE != startH);

	glEnd();
}

void DrawFace(Face* f) {
	Loop* startL;
	Loop* lp;

	glEnable(GL_STENCIL_TEST);
	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_ALWAYS, 1, ~0);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	startL = f->lp;
	lp = f->lp;
	do {
		if (lp != nullptr && lp->isInnerLoop()) {
			Drawing(lp);
		}
		lp = lp->next;
	} while (lp != nullptr && lp != startL);

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_EQUAL, 0, ~0);
	glDepthMask(GL_TRUE);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	startL = f->lp;
	lp = f->lp;
	do {
		if (lp != nullptr && !lp->isInnerLoop()) {
			Drawing(lp);
		}
		lp = lp->next;
	} while (lp != nullptr && lp != startL);

	glDisable(GL_STENCIL_TEST);
}

void DrawSolid(Solid* s) {
	Face* startF = s->faces;
	Face* face = s->faces;
	do {
		if (face != nullptr) {
			DrawFace(face);
		}
		face = face->next;
	} while (face != nullptr && face != startF);
}


void CALLBACK tessBeginCB(GLenum which)
{
	glBegin(which);
}

void CALLBACK tessEndCB()
{
	glEnd();
}

void CALLBACK tessVertexCB(const GLvoid* data)
{
	const GLdouble* ptr = (const GLdouble*)data;

	glColor3dv(ptr + 3);
	glVertex3dv(ptr);
}
