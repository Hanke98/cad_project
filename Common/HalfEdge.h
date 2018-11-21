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

    HalfEdge(Vertex *vtx);

    virtual ~HalfEdge();

    HalfEdge *getNext_he() const;

    void setNext_he(HalfEdge *next_he);

    HalfEdge *getPrev_he() const;

    void setPrev_he(HalfEdge *prev_he);

    Edge *getEdg() const;

    void setEdg(Edge *edg);

    Loop *getWloop() const;

    void setWloop(Loop *wloop);

    Vertex *getVtx() const;

    void setVtx(Vertex *vtx);

private:
    HalfEdge *next_he;
    HalfEdge *prev_he;
    Edge *edg;
    Loop *wloop;
    Vertex *vtx;

};


#endif //CAD_FINAL_HALFEDGE_H
