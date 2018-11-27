//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_EULAROPERATION_H
#define CAD_FINAL_EULAROPERATION_H

#include "../Common/Solid.h"
#include "../Common/Edge.h"

class EularOperation {
public:
    static Solid *mvsf(Vertex *&v);
    static HalfEdge *mev(Vertex *&v1, Vertex *&v2, Loop *&l);
    static Face *mef(Vertex *&v1, Vertex *&v2, Loop *&l);
    static Loop *kemr(Vertex *&v1, Vertex *&v2, Loop *&l);
//    static Face *kemr(Vertex *&v1);
};


#endif //CAD_FINAL_EULAROPERATION_H
