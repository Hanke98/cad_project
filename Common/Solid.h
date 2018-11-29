//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_SOLID_H
#define CAD_FINAL_SOLID_H

#include "Face.h"
#include <vector>
#include <iostream>


class Solid {
public:

    Solid();

    virtual ~Solid();

    Solid *getPrev_s() const;

    void setPrev_s(Solid *prev_s);

    Solid *getNext_s() const;

    void setNext_s(Solid *next_s);

    Face *getSfaces() const;

    void setSfaces(Face *sfaces);

    Edge *getSedges() const;

    void setSedges(Edge *sedges);

    void AddVertex(Vertex *& v);

    void AddFaces(Face *f);

    int getNumOfFaces() const;

    const std::vector<Face *> &GetFaces() const;

    void RemoveFace(Face * f);

private:
    Solid *prev_s;
    Solid *next_s;
    Face *sfaces;
    Edge *sedges;
    std::vector<Vertex*> vertexes;
    std::vector<Face*> faces;
};


#endif //CAD_FINAL_SOLID_H
