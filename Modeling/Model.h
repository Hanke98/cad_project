//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_MODELING_H
#define CAD_FINAL_MODELING_H

#include <vector>
#include <deque>
#include "../Common/Solid.h"
#include "../Files/Files.h"

class Model {
public:
    Model();

    void BuildSolid(std::string vtx_path, std::string op_path);

    const Solid *GetSolid() const;

private:
    std::vector<Vertex *> vertexes;
    std::deque<int> operands_q;
    std::vector<int> operands_order;
    Solid *solid;

};


#endif //CAD_FINAL_MODELING_H
