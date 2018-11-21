//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_EDGE_H
#define CAD_FINAL_EDGE_H

#include "HalfEdge.h"

class Edge {
public:
    Edge();

    Edge(HalfEdge *he1, HalfEdge *he2);

    virtual ~Edge();

    HalfEdge *getHe1() const;

    void setHe1(HalfEdge *he1);

    HalfEdge *getHe2() const;

    void setHe2(HalfEdge *he2);

    Edge *getPrev_e() const;

    void setPrev_e(Edge *prev_e);

    Edge *getNext_e() const;

    void setNext_e(Edge *next_e);

private:
    HalfEdge *he1;
    HalfEdge *he2;
    Edge *prev_e;
    Edge *next_e;
};


#endif //CAD_FINAL_EDGE_H
