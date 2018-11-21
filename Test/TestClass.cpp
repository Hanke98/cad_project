//
// Created by Hanke on 2018/10/23.
//

#include "TestClass.h"

void Test::TestReadVertex(std::string vtx_path) {
    std::vector<Vertex *> vs = Files::ReadVertexs(vtx_path);
    for (auto &v : vs) {
        v->PrintPos();
    }
}

void Test::TestReadOp(std::string op_path) {
    std::deque<int> vq;
    std::vector<int> order = Files::ReadOperators(op_path, vq);

    for (auto &o :order) {
        std::cout << o << std::endl;
        int i = 0;
        while (i < OperandsSize[o]) {
            std::cout << vq[0] << ' ';
            vq.pop_front();
            i++;
        }
        std::cout << std::endl;
    }

}

void Test::TestModeling(std::string vtx_path, std::string op_path) {
    auto *model = new Model();

    model->BuildSolid(vtx_path, op_path);

    delete(model);
}

void Test::TestRendering() {
    Render render;
    render.Display();
//    render.Init();

//    render.Display();
}

Test::Test() {

}


