//
// Created by Hanke on 2018/10/23.
//

#include "Edge.h"

Edge::Edge() :
    he1(nullptr),
    he2(nullptr),
    prev_e(nullptr),
    next_e(nullptr)
{}

Edge::~Edge() {

}

Edge::Edge(HalfEdge *he1, HalfEdge *he2) :
        he1(he1),
        he2(he2),
        prev_e(nullptr),
        next_e(nullptr)
{}

HalfEdge *Edge::getHe1() const {
    return he1;
}

void Edge::setHe1(HalfEdge *he1) {
    Edge::he1 = he1;
}

HalfEdge *Edge::getHe2() const {
    return he2;
}

void Edge::setHe2(HalfEdge *he2) {
    Edge::he2 = he2;
}

Edge *Edge::getPrev_e() const {
    return prev_e;
}

void Edge::setPrev_e(Edge *prev_e) {
    Edge::prev_e = prev_e;
}

Edge *Edge::getNext_e() const {
    return next_e;
}

void Edge::setNext_e(Edge *next_e) {
    Edge::next_e = next_e;
}
