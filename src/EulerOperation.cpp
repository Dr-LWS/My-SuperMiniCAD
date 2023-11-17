#include "EulerOperation.h"
#include "HalfEdgeDataStructure.h"

Solid* mvsf(Point p, Vertex*& v) {
	//initial
	Solid* newS = new Solid();
	Face* newF = new Face();
	Loop* newL = new Loop();
	v = new Vertex();

	//load
	v->point = new Point();
	v->point->SetP(p);
	newS->faces = newF;
	newF->solid = newS;
	newF->lp = newL;
	newL->face = newF;

	return newS;
}

HalfEdge* mev(Vertex* v, Point p, Loop* lp) {
	HalfEdge* newHE1 = new HalfEdge();
	HalfEdge* newHE2 = new HalfEdge();
	Edge* newE = new Edge();
	Vertex* newV = new Vertex();
	newV->point = new Point();

	newE->leftHE = newHE1;
	newE->rightHE = newHE2;
	newHE1->edge = newE;
	newHE2->edge = newE;
	newHE1->adjacent = newHE2;
	newHE2->adjacent = newHE1;

	newV->point->SetP(p);
	newHE1->startV = v;
	newHE1->endV = newV;
	newHE2->startV = newV;
	newHE2->endV = v;
	newHE1->lp = lp;
	newHE2->lp = lp;
	newHE1->next = newHE2;
	newHE2->pre = newHE1;

	if (lp->halfedges == nullptr) {
		newHE2->next = newHE1;
		newHE1->pre = newHE2;
		lp->halfedges = newHE1;
	}
	else {
		HalfEdge* ptr;
		for (ptr = lp->halfedges; ptr->next->startV != v; ptr = ptr->next) {}
		newHE2->next = ptr->next;
		ptr->next->pre = newHE2;
		newHE1->pre = ptr;
		ptr->next = newHE1;
	}

	Solid* origin = lp->face->solid;
	Edge* ed = origin->edges;
	if (ed == nullptr) {
		origin->edges = newE;
	}
	else {
		for (; ed->next != nullptr; ed = ed->next) {}
		ed->next = newE;
		newE->pre = ed;
	}

	return newHE1;
}

Loop* mef(Vertex* v1, Vertex* v2, Loop*& lp) {
	HalfEdge* newHE1 = new HalfEdge();
	HalfEdge* newHE2 = new HalfEdge();
	Edge* newE = new Edge();

	newE->leftHE = newHE1;
	newE->rightHE = newHE2;
	newHE1->edge = newE;
	newHE2->edge = newE;
	newHE1->adjacent = newHE2;
	newHE2->adjacent = newHE1;
	newHE1->startV = v1;
	newHE1->endV = v2;
	newHE2->startV = v2;
	newHE2->endV = v1;

	HalfEdge* ptr, * s;
	int detect = 0;
	s = lp->halfedges;
	ptr = lp->halfedges;
	for (ptr = lp->halfedges; ptr->startV != v1; ptr = ptr->next) {
		if (ptr == s && detect == 2) {
			cout << "Cannot find vertex!" << endl;
			return nullptr;
		}
		if (ptr == s && detect != 2) {
			detect++;
		}
	}

	HalfEdge* leftHE = ptr;
	
	s = lp->halfedges;
	ptr = lp->halfedges;
	for (ptr = lp->halfedges; ptr->startV != v2; ptr = ptr->next) {
		if (ptr == s && detect == 2) {
			cout << "Cannot find vertex!" << endl;
			return nullptr;
		}
		if (ptr == s && detect != 2) {
			detect++;
		}
	}

	HalfEdge* rightHE = ptr;

	newHE1->next = rightHE;
	newHE1->pre = leftHE->pre;
	newHE2->next = leftHE;
	newHE2->pre = rightHE->pre;
	leftHE->pre->next = newHE1;
	leftHE->pre = newHE2;
	rightHE->pre->next = newHE2;
	rightHE->pre = newHE1;

	lp->halfedges = newHE1;

	Loop* newLP = new Loop();
	newLP->halfedges = newHE2;

	Solid* origin = lp->face->solid;

	Face* newF = new Face();
	newF->lp = newLP;
	newF->solid = origin;
	newLP->face = newF;

	Face* fptr;
	for (fptr = origin->faces; fptr->next != nullptr; fptr = fptr->next) {}
	fptr->next = newF;
	newF->pre = fptr;

	Edge* ed = origin->edges;
	if (ed == nullptr) {
		origin->edges = newE;
	}
	else {
		for (; ed->next != nullptr; ed = ed->next) {}
		ed->next = newE;
		newE->pre = ed;
	}

	if (newLP->size() > lp->size()) {
		Loop* tp = newLP;
		newLP = lp;
		lp = tp;
	}

	return newLP;
}

Loop* kemr(Vertex* v1, Vertex* v2, Loop*& lp) {
	Loop* newL = new Loop();
	HalfEdge* ptr;
	for (ptr = lp->halfedges; !(ptr->startV == v1 && ptr->endV == v2); ptr = ptr->next) {}

	ptr->next->pre = ptr->adjacent->pre;
	ptr->adjacent->pre->next = ptr->next;
	ptr->pre->next = ptr->adjacent->next;
	ptr->adjacent->next->pre = ptr->pre;
	
	lp->halfedges = ptr->pre;
	newL->halfedges = ptr->next;

	Face* origin = lp->face;
	newL->face = origin;

	Loop* Lptr;
	for (Lptr = origin->lp; Lptr->next != nullptr; Lptr = Lptr->next) {};
	Lptr->next = newL;
	newL->pre = Lptr;

	Solid* originS = lp->face->solid;
	Edge* ed = originS->edges;
	if (ed == ptr->edge) {
		originS->edges = ptr->edge->next;
		originS->edges->pre = ed->pre;
	}
	else {
		for (; ed->next != ptr->edge; ed = ed->next) {};
		ed->next = ptr->edge->next;
		ed->next->pre = ed;
	}

	if (newL->size() > lp->size()) {
		Loop* tp = newL;
		newL = lp;
		lp = tp;
	}

	return newL;
}

void kfmrh(Loop* outterLp, Loop* innerLp) {
	Face* face1 = outterLp->face;
	Face* face2 = innerLp->face;
	Loop* lp;
	for (lp = face1->lp; lp->next != nullptr; lp = lp->next) {}
	lp->next = innerLp;
	innerLp->pre = lp;
	innerLp->face = face1;

	Solid* originS = face1->solid;
	Face* f = originS->faces;
	if (f == face2) {
		originS->faces = f->next;
		originS->faces->pre = f->pre;
	}
	else
	{
		for (; f->next != face2; f = f->next) {}
		f->next = face2->next;
		f->next->pre = f;
	}

	return;
}

Solid* sweep(Face* f, glm::vec3 dir, float dis) {
	Solid* solid = f->solid;
	Loop* lp;
	HalfEdge* HE;

	for (lp = f->lp; lp != nullptr; lp = lp->next) {
		HE = lp->halfedges;
		Vertex* startV = HE->startV;
		glm::vec3 newLoc = startV->point->locate + dir * dis;
		Point newP(newLoc.x, newLoc.y, newLoc.z);

		HalfEdge* connectF = mev(startV, newP, lp);
		Vertex* endV1 = connectF->endV;

		HE = HE->next;
		Vertex* vptr = HE->startV;
		while (vptr != startV) {
			glm::vec3 newLoc = vptr->point->locate + dir * dis;
			Point newP(newLoc.x, newLoc.y, newLoc.z);
			HalfEdge* connect = mev(vptr, newP, lp);
			Vertex* endV2 = connect->endV;
			mef(endV2, endV1, lp);
			endV1 = endV2;
			HE = HE->next;
			vptr = HE->startV;
		}
		mef(connectF->endV, endV1, lp);
	}

	return solid;
}

int Face::size() {
	if (lp == nullptr) {
		return 0;
	}
	else {
		int count = 0;
		Loop* ptr = lp;
		Loop* m = lp;
		do {
			count++;
			m = m->next;
		} while (m != nullptr && m != ptr);
		return count;
	}
}

int Loop::size() {
	if (halfedges == nullptr) {
		return 0;
	}
	else {
		int count = 0;
		HalfEdge* s = halfedges;
		HalfEdge* ptr = halfedges;
		do {
			count++;
			ptr = ptr->next;
		} while (ptr != nullptr && ptr != s);
		return count;
	}
}
