//
// Created by Hanke on 2018/11/8.
//

#include "MeshData.h"

GLuint MeshData::getVAO() const {
    return VAO;
}

void MeshData::setVAO(GLuint VAO) {
    MeshData::VAO = VAO;
}

GLuint MeshData::getVBO() const {
    return VBO;
}

void MeshData::setVBO(GLuint VBO) {
    MeshData::VBO = VBO;
}

glm::mat4 *MeshData::getModel_matrix_pointer() const {
    return model_matrix_pointer;
}

void MeshData::setModel_matrix_pointer(glm::mat4 *model_matrix_pointer) {
    MeshData::model_matrix_pointer = model_matrix_pointer;
}

size_t MeshData::getNum_of_vertex() const {
    return num_of_vertex;
}

void MeshData::setNum_of_vertex(size_t num_of_vertex) {
    MeshData::num_of_vertex = num_of_vertex;
}

MeshData::MeshData(GLuint VAO, GLuint VBO, glm::mat4 *model_matrix_pointer, int num_of_vertex) :
        VAO(VAO), VBO(VBO),
        model_matrix_pointer(model_matrix_pointer),
        num_of_vertex(num_of_vertex) {}

std::ostream &operator<<(std::ostream &os, const MeshData &data) {
    os << "VAO: " << data.VAO << " VBO: " << data.VBO << " model_matrix_pointer: " << data.model_matrix_pointer
       << " num_of_vertex: " << data.num_of_vertex;
    return os;
}
