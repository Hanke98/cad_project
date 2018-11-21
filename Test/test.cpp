//
// Created by Hanke on 2018/10/23.
//

#include <iostream>
#include "TestClass.h"

int main() {
    Test test;
//    test.TestReadVertex("../../src/data/v.txt");
//    test.TestReadOp("../../src/data/op.txt");
    test.TestModeling("../../src/data/v.txt", "../../src/data/op.txt");
//    test.TestRendering();
    return 0;
}