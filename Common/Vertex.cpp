//
// Created by Hanke on 2018/10/22.
//

#include <iostream>
#include "Vertex.h"

Vertex::Vertex(const Eigen::Vector3d &pos) :
        pos(pos),
        normal(Eigen::Vector3d(0, 0, 0)),
        prev_v(nullptr),
        next_v(nullptr) {}

Vertex::Vertex() :
        pos(Eigen::Vector3d(0, 0, 0)),
        normal(Eigen::Vector3d(0, 0, 0)),
        prev_v(nullptr),
        next_v(nullptr) {}

Vertex::~Vertex() {
//    Vertex *p = next_v;
//    while (p) {
//        Vertex *tmp = p;
//        p = p->next_v;
//        delete (tmp);
//    }
}

const Eigen::Vector3d &Vertex::getPos() const {
    return pos;
}

void Vertex::setPos(const Eigen::Vector3d &pos) {
    Vertex::pos = pos;
}

const Eigen::Vector3d &Vertex::getNormal() const {
    return normal;
}

void Vertex::setNormal(const Eigen::Vector3d &normal) {
    Vertex::normal = normal;
}

Vertex *Vertex::getPrev_v() const {
    return prev_v;
}

void Vertex::setPrev_v(Vertex *prev_v) {
    Vertex::prev_v = prev_v;
}

Vertex *Vertex::getNext_v() const {
    return next_v;
}

void Vertex::setNext_v(Vertex *next_v) {
    Vertex::next_v = next_v;
}

Vertex::Vertex(const double &x, const double &y, const double &z) :
        pos(Eigen::Vector3d(x, y, z)),
        normal(Eigen::Vector3d(0, 0, 0)),
        prev_v(nullptr),
        next_v(nullptr) {

}

void Vertex::AddNewVertex() {
    if (!next_v) {
        next_v = new Vertex();
        next_v->setPrev_v(this);
    } else {
        std::cout << "next_v is not null" << std::endl;
    }
}

void Vertex::AddNewVertex(const double &x, const double &y, const double &z) {

    if (!next_v) {
        next_v = new Vertex(x, y, z);
        next_v->setPrev_v(this);
    } else {
        std::cout << "next_v is not null" << std::endl;
    }
}

void Vertex::PrintPos() {
    std::cout << pos[0] << ", " << pos[1] <<", " <<pos[2]<<std::endl;
}

Eigen::Vector3d Vertex::operator-(const Vertex *&v2) {
    return pos - v2->getPos();
}
