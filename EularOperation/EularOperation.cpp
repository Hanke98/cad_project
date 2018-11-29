//
// Created by Hanke on 2018/10/23.
//

#include <iostream>
#include "EularOperation.h"

Solid *EularOperation::mvsf(Vertex *&v) {
    auto *solid = new Solid();
    auto *loop = new Loop;
    auto *f = new Face();

//    solid->setSfaces(f);
    solid->AddFaces(f);
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

    he1->SetPartner(he2);
    he2->SetPartner(he1);

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

        he1->setPrev_he(he);
        he2->setNext_he(he->getNext_he());
        he->getNext_he()->setPrev_he(he2);
        he->setNext_he(he1);
    }
    l->AddHalfEdge(2);
    return he1;
}

Face *EularOperation::mef(Vertex *&v1, Vertex *&v2, Loop *&l) {
    auto *face = new Face();
    auto *new_loop = new Loop();

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

    he1->SetPartner(he2);
    he2->SetPartner(he1);

    he1->setWloop(l);
    he2->setWloop(new_loop);

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

    new_loop->setLedg(he2);
    new_loop->UpdateLoop();
    face->AddInnerLoop(new_loop);
    face->setFsolid(solid);
    solid->AddFaces(face);
    new_loop->setLface(face);

    l->UpdateLoop();
    l->getLface()->setNext_f(face);
    face->setPrev_f(l->getLface());

    return face;
}

Loop *EularOperation::kemr(Vertex *&v1, Vertex *&v2, Loop *&l) {
    auto *new_loop = new Loop();
    auto *face = l->getLface();
    HalfEdge *he, *he_a, *he_b, *he_c, *he_d;

    new_loop->setLface(face);

    he = l->getLedg();
    while (!(he->getStart_v() == v1 && he->getEnd_v() == v2)) {
        he = he->getNext_he();
    }

    he_a = he;
    he = l->getLedg();
    while (!(he->getStart_v() == v2 && he->getEnd_v() == v1)) {
        he = he->getNext_he();
    }
    he_b = he;

    assert(he_a->getNext_he() == he_b);
    he_c = he_a->getPrev_he();
    he_d = he_b->getNext_he();

    he_c->setNext_he(he_d);
    he_d->setPrev_he(he_c);

    delete he_a;
    delete he_b;

    new_loop->UpdateLoop();
    l->UpdateLoop();
    face->AddInnerLoop(new_loop);

    return new_loop;
}

void EularOperation::Sweep(Vertex *&v1, Vertex *&v2, Face *f) {
    auto *l = f->getFloops();
    Eigen::Vector3d d = v2->getPos() - v1->getPos();
    Face *bottom_face = nullptr;
    bool out_loop = true;
    while (l) {
        int num_of_he = l->GetNum_of_he();
        auto *he = l->getLedg();
        auto *v = he->getStart_v();
        auto *pre_up = new Vertex(v->getPos() + d);
        auto *partner_loop = he->GetPartner()->getWloop();
        auto *pre_up_back = pre_up;
        Vertex *next_v, *new_up;
        mev(v, pre_up, partner_loop);
        he = he->getNext_he();

        for (int i = 0; i < num_of_he - 1; i++) {
            next_v = he->getStart_v();
            new_up = new Vertex(next_v->getPos() + d);
            partner_loop = he->GetPartner()->getWloop();
            mev(next_v, new_up, partner_loop);
            auto *new_f = mef(new_up, pre_up, partner_loop);
            he = he->getNext_he();
            pre_up = new_up;
        }
        if (!out_loop) {
            auto *f2 = mef(pre_up, pre_up_back, partner_loop);
            kfmrh(bottom_face,f2);
        } else {
            bottom_face = mef(pre_up, pre_up_back, partner_loop);
        }
        l = l->getNext_l();
        out_loop = false;
    }


}

Loop *EularOperation::kfmrh(Face *f1, Face *f2) {

    auto *lp = f2->getFloops();

    f1->AddInnerLoop(lp);
    auto *solid = f1->getFsolid();
    solid->RemoveFace(f2);

    return nullptr;
}

