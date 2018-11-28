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
    int i = 0;
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
        if (op == KEMR) {
            Vertex *v0 = vertexes[operands_q[0]];
            Vertex *v1 = vertexes[operands_q[1]];
            loop = EularOperation::kemr(v0, v1, loop);
            operands_q.pop_front();
            operands_q.pop_front();
            continue;
        }
        if (op == SWEEP) {
            Vertex *v0 = vertexes[operands_q[0]];
            Vertex *v1 = vertexes[operands_q[1]];
            EularOperation::Sweep(v0, v1, solid->getSfaces());
            operands_q.pop_front();
            operands_q.pop_front();
            continue;
        }


    }

    if (!solid) {
        std::cout << "build solid error" << std::endl;
        return;
    }

    int num_of_face = solid->getNumOfFaces();
    auto face_vector = solid->GetFaces();
    for( int face_order =0 ;face_order < num_of_face; face_order ++) {
        std::cout << "face " << face_order << ": " << std::endl;
        auto *cur_face = face_vector[face_order];
        loop = cur_face->getFloops();
        while (loop) {
            he = loop->getLedg();
            int i = 0;
            while (i < loop->GetNum_of_he()) {
                assert(he);
                std::cout << "he " << ++i << ": " <<  std::endl;
                he->getStart_v()->PrintPos();
                he->getEnd_v()->PrintPos();
                he = he->getNext_he();
            }
            loop = loop->getNext_l();
            std::cout << "\n";
        }
        std::cout << "=========\n";
    }

}
