//
// Created by Hanke on 2018/10/23.
//

#include "Loop.h"
#include "Face.h"


Loop::Loop():
    prev_l(nullptr),
    next_l(nullptr),
    ledg(nullptr),
    lface(nullptr)
{}

Loop::~Loop() {

}

Loop *Loop::getPrev_l() const {
    return prev_l;
}

void Loop::setPrev_l(Loop *prev_l) {
    Loop::prev_l = prev_l;
}

Loop *Loop::getNext_l() const {
    return next_l;
}

void Loop::setNext_l(Loop *next_l) {
    Loop::next_l = next_l;
}

HalfEdge *Loop::getLedg() const {
    return ledg;
}

void Loop::setLedg(HalfEdge *ledg) {
    Loop::ledg = ledg;
}

Face *Loop::getLface() const {
    return lface;
}

void Loop::setLface(Face *lface) {
    Loop::lface = lface;
}
