//
// Created by Hanke on 2018/10/23.
//

#include <iostream>
#include "EularOperation.h"

Solid *EularOperation::mvsf(Vertex *&v) {
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
    he1 = new HalfEdge(v1, v2);
    he2 = new HalfEdge(v2, v1);
    e = new Edge(he1, he2);
    he = nullptr;
    he1->setEdg(e);
    he2->setEdg(e);

    he1->setWloop(l);
    he2->setWloop(l);

    he1->setNext_he(he2);
    he2->setPrev_he(he1);

    if (!l->getLedg()) {
        l->setLedg(he1);
        he1->setPrev_he(he2);
        he2->setNext_he(he1);
    } else {
        he = l->getLedg();
        while (he->getNext_he()->getStart_v() != v1) {
            he = he->getNext_he();
        }
//        he->getStart_v()->PrintPos();
//        he = he->getNext_he();
        he1->setPrev_he(he);
        he2->setNext_he(he->getNext_he());
        he->getNext_he()->setPrev_he(he2);
        he->setNext_he(he1);
    }

    return he1;
}

Face *EularOperation::mef(Vertex *&v1, Vertex *&v2, Loop *&l) {
    auto *face = new Face();
    auto *loop = new Loop();

    Solid *solid = l->getLface()->getFsolid();

    HalfEdge *he1, *he2, *he;
    HalfEdge *the1, *the2, *the3;
    Edge *e;
    he1 = new HalfEdge(v1, v2);
    he2 = new HalfEdge(v2, v1);
    e = new Edge(he1, he2);

    he = l->getLedg();

    he1->setEdg(e);
    he2->setEdg(e);

    he1->setWloop(l);
    he2->setWloop(loop);

    while (he->getEnd_v() != v1) {
        he = he->getNext_he();
    }
    the1 = he;

    he = l->getLedg();
    while (he->getStart_v() != v2) {
        he = he->getNext_he();
    }
    the2 = he;

    he = l->getLedg();
    while (he->getEnd_v() != v2) {
        he = he->getNext_he();
    }
    the3 = he;

    he1->setPrev_he(the1);
    the1->getNext_he()->setPrev_he(he2);

    he2->setNext_he(the1->getNext_he());
    the1->setNext_he(he1);

    he1->setNext_he(the2);
    the2->setPrev_he(he1);

    he2->setPrev_he(the3);
    the3->setNext_he(he2);

    loop->setLedg(he2);
    face->setFloops(loop);
    solid->AddFaces(face);

    l->getLface()->setNext_f(face);
    face->setPrev_f(l->getLface());

    he = l->getLedg();
    while(he->getNext_he()->getStart_v() != l->getLedg()->getStart_v()) {
//        he->getStart_v()->PrintPos();
//        he->getEnd_v()->PrintPos();
//        std::cout<< "===" << std::endl;
        he = he->getNext_he();
    }
//    he->getStart_v()->PrintPos();
//    he->getEnd_v()->PrintPos();
//    std::cout<< "===" << std::endl;
    return face;
}

Loop *EularOperation::kemr(Vertex *&v1, Vertex *&v2, Loop *&l) {
    auto *new_loop = new Loop();
    auto *face = l->getLface();
    HalfEdge *he, *he_a, *he_b, *he_c, *he_d;

    new_loop->setLface(face);

    he = l->getLedg();
    while (!(he->getStart_v() == v1 && he->getEnd_v() == v2)) {
//        he->getStart_v()->PrintPos();
//        he->getEnd_v()->PrintPos();
//        std::cout << "====" << std::endl;
        he = he->getNext_he();
    }
//    he->getStart_v()->PrintPos();
//    he->getEnd_v()->PrintPos();
//    std::cout << "====" << std::endl;
//    he->getPrev_he()->getStart_v()->PrintPos();
//    he->getPrev_he()->getEnd_v()->PrintPos();
//    std::cout << "====" << std::endl;
    he_a = he;

    he = l->getLedg();
    while (!(he->getStart_v() == v2 && he->getEnd_v() == v1)) {
        he = he->getNext_he();
    }
    he_b = he;

    assert(he_a->getNext_he() == he_b);
    he_c = he_a->getPrev_he();
    he_d = he_b->getNext_he();

//    he_a->getStart_v()->PrintPos();
//    he_b->getStart_v()->PrintPos();
//    he_c->getStart_v()->PrintPos();
//    he_d->getStart_v()->PrintPos();
//
//    std::cout << "=====" << std::endl;
//
//    he_a->getEnd_v()->PrintPos();
//    he_b->getEnd_v()->PrintPos();
//    he_c->getEnd_v()->PrintPos();
//    he_d->getEnd_v()->PrintPos();

    he_c->setNext_he(he_d);
    he_d->setPrev_he(he_c);

    delete he_a;
    delete he_b;

    auto *loop_itr = l;
    while (loop_itr->getNext_l())
        loop_itr = loop_itr->getNext_l();
    loop_itr->setNext_l(new_loop);

    return new_loop;
}
