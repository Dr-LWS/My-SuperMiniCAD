#pragma once

#include "HalfEdgeDataStructure.h"
#include "EulerOperation.h"
#include "Drawing.h"

Solid* CreateCube() {
	Solid* newS;
	Vertex* startV;
	newS = mvsf(Point(-0.5, 0.5, 0.5), startV);
	Loop* lp = newS->faces->lp;

	HalfEdge* V1 = mev(startV, Point(0.5, 0.5, 0.5), lp);
	Vertex* V2 = V1->endV;

    HalfEdge* V3 = mev(startV, Point(-0.5, 0.5, -0.5), lp);
    Vertex* V4 = V3->endV;

    HalfEdge* V5 = mev(V2, Point(0.5, 0.5, -0.5), lp);
    Vertex* V6 = V5->endV;

    Loop* downLoop = mef(V4, V6, lp);

    sweep(lp->face, glm::vec3(0, -1, 0), 1);

    return newS;
}

Solid* CreateTunnel() {
    Solid* newS;
    Vertex* V0;
    newS = mvsf(Point(-1.0, 2.0, 1.0), V0);
    Loop* Lp0 = newS->faces->lp;

    HalfEdge* E0 = mev(V0, Point(1.0, 2.0, 1.0), Lp0);
    Vertex* V1 = E0->endV;

    HalfEdge* E1 = mev(V0, Point(-1.0, 2.0, -1.0), Lp0);
    Vertex* V2 = E1->endV;

    HalfEdge* E2 = mev(V1, Point(1.0, 2.0, -1.0), Lp0);
    Vertex* V3 = E2->endV;

    Loop* Lp1 = mef(V2, V3, Lp0);

    HalfEdge* E4 = mev(V0, Point(-1.0, -2.0, 1.0), Lp1);
    Vertex* V4 = E4->endV;
    HalfEdge* E5 = mev(V1, Point(1.0, -2.0, 1.0), Lp1);
    Vertex* V5 = E5->endV;
    HalfEdge* E6 = mev(V2, Point(-1.0, -2.0, -1.0), Lp1);
    Vertex* V6 = E6->endV;
    HalfEdge* E7 = mev(V3, Point(1.0, -2.0, -1.0), Lp1);
    Vertex* V7 = E7->endV;

    Loop* Lp2 = mef(V4, V5, Lp1);
    Loop* Lp3 = mef(V5, V7, Lp1);
    Loop* Lp4 = mef(V7, V6, Lp1);
    Loop* Lp5 = mef(V6, V4, Lp1);

    HalfEdge* E8 = mev(V0, Point(-0.5, 2.0, 0.5), Lp0);

    Vertex* V8 = E8->endV;

    HalfEdge* E9 = mev(V8, Point(0.5, 2.0, 0.5), Lp0);
    Vertex* V9 = E9->endV;
    HalfEdge* E10 = mev(V9, Point(0.5, 2.0, -0.5), Lp0);
    Vertex* V10 = E10->endV;
    HalfEdge* E11 = mev(V8, Point(-0.5, 2.0, -0.5), Lp0);
    Vertex* V11 = E11->endV;
    Loop* Lp6 = mef(V11, V10, Lp0);

    Loop* Lp7 = kemr(V0, V8, Lp0);

    HalfEdge* E12 = mev(V8, Point(-0.5, -2.0, 0.5), Lp6);
    Vertex* V12 = E12->endV;
    HalfEdge* E13 = mev(V9, Point(0.5, -2.0, 0.5), Lp6);
    Vertex* V13 = E13->endV;
    HalfEdge* E14 = mev(V11, Point(-0.5, -2.0, -0.5), Lp6);
    Vertex* V14 = E14->endV;
    HalfEdge* E15 = mev(V10, Point(0.5, -2.0, -0.5), Lp6);
    Vertex* V15 = E15->endV;

    Loop* Lp8 = mef(V12, V13, Lp6);
    Loop* Lp9 = mef(V13, V15, Lp6);
    Loop* Lp10 = mef(V15, V14, Lp6);
    Loop* Lp11 = mef(V14, V12, Lp6);

    kfmrh(Lp1, Lp6);

    Lp7->setInner(true);
    Lp6->setInner(true);

    return newS;
}

Solid* CreatePyramid(){
    Solid* newS;
    Vertex* V0;
    newS = mvsf(Point(0.0, -2.0, 0.0), V0);
    Loop* Lp0 = newS->faces->lp;

    HalfEdge* E0 = mev(V0, Point(1.7, 1.0, 0.0), Lp0);
    Vertex* V1 = E0->endV;

    HalfEdge* E1 = mev(V1, Point(-1.7, 1.0, 0.0), Lp0);
    Vertex* V2 = E1->endV;

    Loop* Lp1 = mef(V2, V0, Lp0);

    HalfEdge* E4 = mev(V0, Point(0.0, 0.0, -2.0), Lp1);
    Vertex* V3 = E4->endV;

    Loop* Lp2 = mef(V3, V1, Lp1);
    Loop* Lp3 = mef(V2, V3, Lp1);

    return newS;
}
