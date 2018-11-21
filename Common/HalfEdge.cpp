//
// Created by Hanke on 2018/10/22.
//

#include "HalfEdge.h"
#include "Edge.h"
#include "Loop.h"

HalfEdge::HalfEdge() :
        next_he(nullptr),
        prev_he(nullptr),
        wloop(nullptr),
        edg(nullptr),
        vtx(nullptr)
{}

HalfEdge::~HalfEdge() {

}

HalfEdge *HalfEdge::getNext_he() const {
    return next_he;
}

void HalfEdge::setNext_he(HalfEdge *next_he) {
    HalfEdge::next_he = next_he;
}

HalfEdge *HalfEdge::getPrev_he() const {
    return prev_he;
}

void HalfEdge::setPrev_he(HalfEdge *prev_he) {
    HalfEdge::prev_he = prev_he;
}

Edge *HalfEdge::getEdg() const {
    return edg;
}

void HalfEdge::setEdg(Edge *edg) {
    HalfEdge::edg = edg;
}

Loop *HalfEdge::getWloop() const {
    return wloop;
}

void HalfEdge::setWloop(Loop *wloop) {
    HalfEdge::wloop = wloop;
}

Vertex *HalfEdge::getVtx() const {
    return vtx;
}

void HalfEdge::setVtx(Vertex *vtx) {
    HalfEdge::vtx = vtx;
}

HalfEdge::HalfEdge(Vertex *vtx) :
        next_he(nullptr),
        prev_he(nullptr),
        wloop(nullptr),
        edg(nullptr),
        vtx(vtx)
{}
