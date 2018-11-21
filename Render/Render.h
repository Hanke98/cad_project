//
// Created by Hanke on 2018/11/1.
//

#ifndef CAD_FINAL_RENDER_H
#define CAD_FINAL_RENDER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include "Camera.h"
//#include "../Common/Mesh.h"
#include "../Common/MeshData.h"

class Render {

public:
    Render();

    void Init();

    void InitShader(std::string v_glsl, std::string f_glsl);

    void Display(GLuint prog_id = 0);

    void InsertVAO(int vao);

    void InsertVBO(int vbo);

    void InsertMeshData(MeshData &md);

    void InsertMeshData(GLuint _vao, GLuint _vbo, glm::mat4 *_mm_ptr, size_t _num_of_vertex);

    bool DisplayOneFrame(GLuint prog_id);

    void ClearMeshData();

protected:

    GLuint LoadShader(const char *vertex_file_path, const char *fragment_file_path);

    std::string ReadShaderFile(const char *file_path);

    void CompileShaders(GLuint ID, const char *ShaderPointer);

    GLint Check(GLuint ID);

    static void MouseFunc(GLFWwindow *window, double xpos, double ypos);

    void ProcessInput();

    void DrawMesh();

    void DrawFloor();

    void InitFloor();

private:
    GLFWwindow *window;
    std::vector<GLuint> program_handles;

    std::vector<GLuint> VAOs;
    std::vector<GLuint> VBOs;

    std::vector<MeshData> mesh_data;

    const int SRC_WIDTH = 600;
    static Camera *camera;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    GLint projection_location;
    GLint view_location;
    GLint model_location;
};


#endif //CAD_FINAL_RENDER_H
