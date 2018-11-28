//
// Created by Hanke on 2018/10/23.
//

#include "Face.h"
#include "Solid.h"

Face::Face() :
    prev_f(nullptr),
    next_f(nullptr),
    floops(nullptr),
    num_of_inner_loop(0)
{}

Face::~Face() {

}

Face *Face::getPrev_f() const {
    return prev_f;
}

void Face::setPrev_f(Face *prev_f) {
    Face::prev_f = prev_f;
}

Face *Face::getNext_f() const {
    return next_f;
}

void Face::setNext_f(Face *next_f) {
    Face::next_f = next_f;
}

Loop *Face::getFloops() const {
    return floops;
}

void Face::setFloops(Loop *floops) {
    if(!floops)
        delete(floops);
    Face::floops = floops;
}

Solid *Face::getFsolid() const {
    return fsolid;
}

void Face::setFsolid(Solid *fsolid) {
//    if (Face::fsolid)
//        delete(fsolid);
    Face::fsolid = fsolid;
}

int Face::GetNum_of_inner_loop() const {
    return num_of_inner_loop;
}

void Face::SetNum_of_inner_loop(int num_of_inner_loop) {
    Face::num_of_inner_loop = num_of_inner_loop;
}

void Face::AddInnerLoop(Loop *&l) {
    Loop * loop = floops;

    if (!floops) {
        // if there is no loop in this face
        floops = l;
    }
    else {
        while(loop->getNext_l()) {
            loop = loop->getNext_l();
        }
        loop->setNext_l(l);
        l->setPrev_l(loop);
    }
    num_of_inner_loop += 1;
}
