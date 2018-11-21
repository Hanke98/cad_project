//
// Created by Hanke on 2018/10/23.
//

#include "Model.h"
#include "../EularOperation/EularOperation.h"

Model::Model() {}

void Model::BuildSolid(std::string vtx_path, std::string op_path) {
    vertexes = Files::ReadVertexs(vtx_path);
    operands_order = Files::ReadOperators(op_path, operands_q);
    Solid *solid = nullptr;
    Loop *loop = nullptr;
    HalfEdge *he = nullptr;
    if (operands_order[0] != MVSF) {
        std::cout << "error! the first operator has to be mvsf" << std::endl;
    }
    for (auto &op: operands_order) {
        if (op == MVSF) {
            Vertex *v = vertexes[operands_q[0]];
            solid = EularOperation::mvsf(v);
            loop = solid->getSfaces()->getFloops();
            operands_q.pop_front();
            continue;
        }

        if (op == MEV) {
            Vertex *v0 = vertexes[operands_q[0]];
            Vertex *v1 = vertexes[operands_q[1]];
            he = EularOperation::mev(v0, v1, loop);
            operands_q.pop_front();
            operands_q.pop_front();
            continue;
        }
        if (op == MEF) {
            Vertex *v0 = vertexes[operands_q[0]];
            Vertex *v1 = vertexes[operands_q[1]];
            Face *face = EularOperation::mef(v0, v1, loop);
            // todo add face to solid;
            operands_q.pop_front();
            operands_q.pop_front();
            continue;
        }

    }

    if (!solid) {
        std::cout << "build solid error" << std::endl;
        return;
    }

    loop = solid->getSfaces()->getFloops();
    while(loop) {
        he = loop->getLedg();
        while(he->getNext_he() != loop->getLedg()) {
            he->getVtx()->PrintPos();
            he = he->getNext_he();
        }
        he->getVtx()->PrintPos();
        loop = loop->getNext_l();
        std::cout << "\n";
    }
}
