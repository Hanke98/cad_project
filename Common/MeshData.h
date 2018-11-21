//
// Created by Hanke on 2018/11/8.
//

#ifndef ROBOT_MESHDATA_H
#define ROBOT_MESHDATA_H


#include "GL/glew.h"
#include "glm/detail/type_mat.hpp"
#include <ostream>

class MeshData {
public:
    GLuint getVAO() const;

    void setVAO(GLuint VAO);

    MeshData(GLuint VAO, GLuint VBO, glm::mat4 *model_matrix_pointer, int num_of_vertex);

    GLuint getVBO() const;

    void setVBO(GLuint VBO);

    glm::mat4 *getModel_matrix_pointer() const;

    void setModel_matrix_pointer(glm::mat4 *model_matrix_pointer);

    size_t getNum_of_vertex() const;

    void setNum_of_vertex(size_t num_of_vertex);

    friend std::ostream &operator<<(std::ostream &os, const MeshData &data);

private:
    GLuint VAO, VBO;
    glm::mat4 *model_matrix_pointer;
    size_t num_of_vertex;
};


#endif //ROBOT_MESHDATA_H
