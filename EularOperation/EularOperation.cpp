//
// Created by Hanke on 2018/10/23.
//

#include <iostream>
#include "EularOperation.h"

Solid * EularOperation::mvsf(Vertex *&v) {
    auto *solid = new Solid();
    auto *loop = new Loop;
    auto *f = new Face();

    solid->setSfaces(f);
    f->setFsolid(solid);
    f->setFloops(loop);
    loop->setLface(f);
    solid->AddVertex(v);

    return solid;
}

HalfEdge *EularOperation::mev(Vertex *&v1, Vertex *&v2, Loop *&l) {
    HalfEdge *he1, *he2, *he;
    Edge *e;
    he1 = new HalfEdge(v1);
    he2 = new HalfEdge(v2);
    e = new Edge(he1, he2);
    he = nullptr;
    he1->setEdg(e);
    he2->setEdg(e);

    he1->setWloop(l);
    he2->setWloop(l);

    he1->setNext_he(he2);
    he2->setPrev_he(he1);

    if(!l->getLedg()) {
        l->setLedg(he1);
        he1->setPrev_he(he2);
        he2->setNext_he(he1);
    }
    else {
        he = l->getLedg();
        while(he->getNext_he()->getVtx() != v1) {
            he = he->getNext_he();
        }
        he1->setPrev_he(he);
        he2->setNext_he(he->getNext_he());
        he->setNext_he(he1);
        he->getNext_he()->setPrev_he(he2);
    }

    return he1;
}

Face *EularOperation::mef(Vertex *&v1, Vertex *&v2, Loop *&l) {
    auto *face = new Face();
    auto *loop = new Loop();

    Solid *solid = l->getLface()->getFsolid();

    HalfEdge *he1, *he2, *he;
    Edge *e;
    he1 = new HalfEdge(v1);
    he2 = new HalfEdge(v2);
    e = new Edge(he1, he2);

    he = l->getLedg();

    he1->setEdg(e);
    he2->setEdg(e);

    he1->setWloop(l);
    he2->setWloop(l);

    he1->setNext_he(he2);
    he2->setPrev_he(he1);


    while(he->getNext_he()->getVtx() != v1) {
        he = he->getNext_he();
    }

    he1->setPrev_he(he);
    he2->setNext_he(he->getNext_he());
    he->setNext_he(he1);
    he->getNext_he()->setPrev_he(he2);


    he = l->getLedg();
    while(he->getVtx()!=v2) {
        he = he->getNext_he();
    }

    he1->setNext_he(he);
    he2->setPrev_he(he->getPrev_he());
    he->setPrev_he(he1);
    he2->getPrev_he()->setNext_he(he2);
    loop->setLedg(he2->getPrev_he());

    l->setNext_l(loop);
    loop->setPrev_l(l);
    solid->AddFaces(face);

    return face;
}
