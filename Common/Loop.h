//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_LOOP_H
#define CAD_FINAL_LOOP_H

#include "HalfEdge.h"
class Face;

class Loop {
public:
    Loop();

    virtual ~Loop();

    Loop *getPrev_l() const;

    void setPrev_l(Loop *prev_l);

    Loop *getNext_l() const;

    void setNext_l(Loop *next_l);

    HalfEdge *getLedg() const;

    void setLedg(HalfEdge *ledg);

    Face *getLface() const;

    void setLface(Face *lface);

    int GetNum_of_he() const;

    void SetNum_of_he(int num_of_he);

    void AddHalfEdge(int num);

    void UpdateLoop();

    void PrintLoop();

private:
    Loop *prev_l;
    Loop *next_l;
    HalfEdge *ledg;
    Face *lface;
    int num_of_he;
};


#endif //CAD_FINAL_LOOP_H
