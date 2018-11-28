//
// Created by Hanke on 2018/10/23.
//

#include <iostream>
#include "Loop.h"
#include "Face.h"


Loop::Loop() :
        prev_l(nullptr),
        next_l(nullptr),
        ledg(nullptr),
        lface(nullptr),
        num_of_he(0) {}

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

int Loop::GetNum_of_he() const {
    return num_of_he;
}

void Loop::SetNum_of_he(int num_of_he) {
    Loop::num_of_he = num_of_he;
}

void Loop::AddHalfEdge(int num = 1) {
    assert (num == 1 || num == 2);
    num_of_he += num;
}

void Loop::UpdateLoop() {
    auto *he = ledg;
    if (!he) {
        num_of_he = 0;
        return;
    }

    num_of_he = 1;
    while (he->getNext_he() != ledg) {
        he->setWloop(this);
        he = he->getNext_he();
        num_of_he += 1;
    }
    he->setWloop(this);
}

void Loop::PrintLoop() {
    UpdateLoop();
    HalfEdge *he = ledg;
    for (int i = 0; i < num_of_he; i++) {
        he->getStart_v()->PrintPos();
        he->getEnd_v()->PrintPos();
        std::cout << "====" << std::endl;
        he = he->getNext_he();
    }
}
