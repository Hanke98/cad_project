//
// Created by Hanke on 2018/10/22.
//

#ifndef CAD_FINAL_HALFEDGE_H
#define CAD_FINAL_HALFEDGE_H

#include "Vertex.h"

class Edge;
class Loop;

class HalfEdge {

public:
    HalfEdge();

    HalfEdge(Vertex *vtx, Vertex *end_v);

    virtual ~HalfEdge();

    HalfEdge *getNext_he() const;

    void setNext_he(HalfEdge *next_he);

    HalfEdge *getPrev_he() const;

    void setPrev_he(HalfEdge *prev_he);

    Edge *getEdg() const;

    void setEdg(Edge *edg);

    Loop *getWloop() const;

    void setWloop(Loop *wloop);

    Vertex *getStart_v() const;

    void setVtx(Vertex *vtx);

    Vertex *getEnd_v() const;

private:
    HalfEdge *next_he;
    HalfEdge *prev_he;
    Edge *edg;
    Loop *wloop;
    Vertex *start_v;
    Vertex *end_v;

};


#endif //CAD_FINAL_HALFEDGE_H
