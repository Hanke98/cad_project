//
// Created by Hanke on 2018/10/23.
//

#include "Solid.h"

Solid::Solid():
    prev_s(nullptr),
    next_s(nullptr),
    sfaces(nullptr),
    sedges(nullptr)
{}

Solid::~Solid() {

}

Solid *Solid::getPrev_s() const {
    return prev_s;
}

void Solid::setPrev_s(Solid *prev_s) {
    Solid::prev_s = prev_s;
}

Solid *Solid::getNext_s() const {
    return next_s;
}

void Solid::setNext_s(Solid *next_s) {
    Solid::next_s = next_s;
}

Face *Solid::getSfaces() const {
    return sfaces;
}

void Solid::setSfaces(Face *sfaces) {
    Solid::sfaces = sfaces;
}

Edge *Solid::getSedges() const {
    return sedges;
}

void Solid::setSedges(Edge *sedges) {
    Solid::sedges = sedges;
}

void Solid::AddVertex(Vertex *&v) {
    vertexes.push_back(v);
}

void Solid::AddFaces(Face *f) {
    faces.push_back(f);
    Face * tf = sfaces;
    if (!tf) {
        sfaces = f;
        return;
    }

    while(tf->getNext_f())
        tf = tf->getNext_f();
    tf->setNext_f(f);
}

int Solid::getNumOfFaces() const {
    return static_cast<int>(faces.size());
}

const std::vector<Face *> &Solid::GetFaces() const {
    return faces;
}
