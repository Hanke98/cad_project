//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_FIL_H
#define CAD_FINAL_FIL_H


#include "../Common/Vertex.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <deque>
#include "../EularOperation/Operands.h"

class Files {
public:
    static std::vector<Vertex*> ReadVertexs(std::string vtx_path);
    static std::vector<int> ReadOperators(std::string op_path, std::deque<int> &operands_q);

private:
    static void ReadOperands(const int op, std::ifstream &file, std::vector<int> &op_order, std::deque<int> &vq);
};


#endif //CAD_FINAL_FIL_H
