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

private:
    Loop *prev_l;
    Loop *next_l;
    HalfEdge *ledg;
    Face *lface;
};


#endif //CAD_FINAL_LOOP_H
