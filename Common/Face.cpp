//
// Created by Hanke on 2018/10/23.
//

#include "Face.h"
#include "Solid.h"

Face::Face() :
    prev_f(nullptr),
    next_f(nullptr),
    floops(nullptr)
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
    if (Face::fsolid)
        delete(fsolid);
    Face::fsolid = fsolid;
}
