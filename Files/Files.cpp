//
// Created by Hanke on 2018/10/23.
//


#include "Files.h"

std::vector<Vertex *> Files::ReadVertexs(std::string vtx_path) {
    std::vector<Vertex *> vs;
    std::ifstream file(vtx_path);
    int lines;

    file >> lines;

    int i = 0;
    while (i < lines) {
        double x = 0, y = 0, z = 0;
        file >> x >> y >> z;
        auto *vertex = new Vertex(x, y, z);
        vs.emplace_back(vertex);
        i++;
    }

    file.close();
    return vs;
}

std::vector<int> Files::ReadOperators(std::string op_path, std::deque<int> &operands_q) {
    std::vector<int> op_order;
    std::ifstream file(op_path);
    int lines;
    file >> lines;
    int i = 0;
    while (i < lines) {
        std::string op;
        file >> op;
        i++;
        if (op.find("mvsf") != std::string::npos) {
            ReadOperands(MVSF, file, op_order, operands_q);
            continue;
        }
        if (op.find("mev") != std::string::npos) {
            ReadOperands(MEV, file, op_order, operands_q);
            continue;
        }
        if (op.find("mef") != std::string::npos) {
            ReadOperands(MEF, file, op_order, operands_q);
            continue;
        }
        if (op.find("kemr") != std::string::npos) {
            ReadOperands(KEMR, file, op_order, operands_q);
            continue;
        }
        if (op.find("sweep") != std::string::npos) {
            ReadOperands(SWEEP, file, op_order, operands_q);
            continue;
        }
    }
    return op_order;
}

void Files::ReadOperands(const int op, std::ifstream &file, std::vector<int> &op_order, std::deque<int> &vq) {
    op_order.push_back(op);
    int t = 0;
    while (t < OperandsSize[op]) {
        int v = 0;
        file >> v;
        vq.emplace_back(v);
        t++;
    }
}
