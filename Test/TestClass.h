//
// Created by Hanke on 2018/10/23.
//

#ifndef CAD_FINAL_TEST_H
#define CAD_FINAL_TEST_H

#include "../Files/Files.h"
#include "../Modeling/Model.h"
#include "../Render/Render.h"

class Test {
public:
    Test();

public:
    void TestReadVertex(std::string vtx_path);
    void TestReadOp(std::string op_path);
    void TestModeling(std::string vtx_path, std::string op_path);
    void TestRendering();
};


#endif //CAD_FINAL_TEST_H
