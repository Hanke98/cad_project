//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_FACE_H
#define CAD_FINAL_FACE_H

#include "Loop.h"
class Solid;

class Face {
public:
    Face();

    virtual ~Face();

    Face *getPrev_f() const;

    void setPrev_f(Face *prev_f);

    Face *getNext_f() const;

    void setNext_f(Face *next_f);

    Loop *getFloops() const;

    void setFloops(Loop *floops);

    Solid *getFsolid() const;

    void setFsolid(Solid *fsolid);

    int GetNum_of_inner_loop() const;

    void SetNum_of_inner_loop(int num_of_inner_loop);

    void AddInnerLoop(Loop *&l);
private:
    Face *prev_f;
    Face *next_f;
    Loop *floops;
    Solid *fsolid;
    int num_of_inner_loop;
};


#endif //CAD_FINAL_FACE_H
