//
// Created by Hanke on 2018/11/1.
//


#include "Render.h"
#include "../Common/Solid.h"

auto *Render::camera = new Camera();

Render::Render() :
        model(glm::mat4(1.0f)),
        view(glm::mat4(1.0f)),
        projection(glm::mat4(1.0f)) {
    window = nullptr;
    Init();
    InitShader("../../src/glsl/v.gsl", "../../src/glsl/f.gsl");
}

void Render::Init() {

    if (!glfwInit()) {
        std::cout << "init GLFW error" << std::endl;
        return;
    }
    glfwWindowHint(GL_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(SRC_WIDTH, SRC_WIDTH, "hello", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "create window error" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "init GL error" << std::endl;
        glfwTerminate();
        return;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseFunc);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    projection = glm::perspective(glm::radians(60.0f), 1.0f, 0.1f, 500.0f);

}

void Render::InitShader(std::string v_glsl, std::string f_glsl) {
    GLuint id = LoadShader(v_glsl.c_str(), f_glsl.c_str());
    program_handles.push_back(id);
}

GLuint Render::LoadShader(const char *vertex_file_path, const char *fragment_file_path) {
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    // load file
    std::string VertexShaderCode = ReadShaderFile(vertex_file_path);
    std::string FragmentShaderCode = ReadShaderFile(fragment_file_path);
    // compile shader
    CompileShaders(VertexShaderID, VertexShaderCode.c_str());
    CompileShaders(FragmentShaderID, FragmentShaderCode.c_str());

    std::cout << "Linking program" << std::endl;
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    Check(ProgramID);

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    return ProgramID;
}

std::string Render::ReadShaderFile(const char *file_path) {
    std::string ShaderCode;
    std::ifstream ShaderCodeStream(file_path, std::ios::in);
    if (ShaderCodeStream.is_open()) {
        std::stringstream sstr;
        sstr << ShaderCodeStream.rdbuf();
        ShaderCode = sstr.str();
        ShaderCodeStream.close();
    } else {
        std::cout << "Impossible to open " << file_path << ".\n";
        return "";
    }
    return ShaderCode;
}

void Render::CompileShaders(GLuint ID, const char *ShaderPointer) {
    glShaderSource(ID, 1, &ShaderPointer, nullptr);
    glCompileShader(ID);
    Check(ID);
}

GLint Render::Check(GLuint ID) {
    GLint Result = GL_FALSE;
    int InfoLogLength = 0;
    if (glIsShader(ID)) {
        glGetShaderiv(ID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    } else {
        glGetProgramiv(ID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    }

    if (InfoLogLength > 0) {
        std::vector<char> ErrorMessage(InfoLogLength + 1);
        if (glIsShader(ID)) {
            glGetShaderInfoLog(ID, InfoLogLength, nullptr, &ErrorMessage[0]);
        } else
            glGetProgramInfoLog(ID, InfoLogLength, nullptr, &ErrorMessage[0]);
        for (int i = 0; i < ErrorMessage.size(); i++) {
            std::cout << ErrorMessage[i];
        }
        std::cout << std::endl;
    }
    return Result;
}

void Render::Display( GLuint prog_id) {

    assert(prog_id < program_handles.size());

    GLuint ProgramID = program_handles[prog_id];
    projection_location = glGetUniformLocation(ProgramID, "projection");
    view_location = glGetUniformLocation(ProgramID, "view");
    model_location = glGetUniformLocation(ProgramID, "model");

    do {
        glUseProgram(ProgramID);
        ProcessInput();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
        view = camera->ViewMatrix();
        glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        DrawMesh();
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);

}

void Render::DrawMesh() {
    glBindVertexArray(VAOs[0]);
    const auto &faces = solid->GetFaces();
    for (const auto &f:faces) {
        auto *loop = f->getFloops()->getNext_l();
        while (loop) {
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
            glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
            glDepthMask(GL_FALSE);
            glStencilMask(0xFF);

            glDrawArrays(GL_TRIANGLE_FAN, loop->GetIdx(), loop->GetNum_of_he());
            loop = loop->getNext_l();
        }

        loop = f->getFloops();
        glStencilFunc(GL_EQUAL, 0, 0xFF);
        glDepthMask(GL_TRUE);
        glStencilOp(GL_ZERO, GL_KEEP, GL_KEEP);
        glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
        glDrawArrays(GL_TRIANGLE_FAN, loop->GetIdx(), loop->GetNum_of_he());

        glStencilMask(0xFF);
    }
    glBindVertexArray(0);

}

void Render::MouseFunc(GLFWwindow *window, double xpos, double ypos) {
    camera->mouseMove(xpos, ypos);
}

void Render::ProcessInput() {
    float cameraSpeed = 0.5f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveForward(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveBackward(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveLeft(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveRight(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void Render::InsertVAO(int vao) {
    VAOs.emplace_back(vao);
}

void Render::InsertVBO(int vbo) {
    VBOs.emplace_back(vbo);
}

// todo draw joint point
bool Render::DisplayOneFrame(GLuint prog_id) {

    assert(prog_id < program_handles.size());

    GLuint ProgramID = program_handles[prog_id];
    projection_location = glGetUniformLocation(ProgramID, "projection");
    view_location = glGetUniformLocation(ProgramID, "view");
    model_location = glGetUniformLocation(ProgramID, "model");

    glUseProgram(ProgramID);
    ProcessInput();
    view = camera->ViewMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
    DrawFloor();
    glfwSwapBuffers(window);
    glfwPollEvents();
    return glfwWindowShouldClose(window) == GL_TRUE;
}


void Render::DrawFloor() {

    glBindVertexArray(VAOs[0]);
    glm::mat4 floor_mat = glm::mat4(1.0);
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(floor_mat));

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Render::InitFloor() {
    GLfloat size = 20.0f;
    GLfloat floor_data[] = {
            -size, 0.f, size, 0, 1, 0,
            -size, 0.f, -size, 0, 1, 0,
            size, 0.f, -size, 0, 1, 0,
            size, 0.f, -size, 0, 1, 0,
            size, 0.f, size, 0, 1, 0,
            -size, 0.f, size, 0, 1, 0
    };

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_data), floor_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    VAOs.push_back(vao);
    VBOs.push_back(vbo);

}

void Render::InitSolidData(const Solid *&solid) {
    // todo modify here
    this->solid = const_cast<Solid *>(solid);

    const int num_of_face = solid->getNumOfFaces();
    const auto &faces = solid->GetFaces();
    std::vector<GLfloat> vertex_data;
    for (const auto &f:faces) {
        auto *loop = f->getFloops();
        while (loop) {
            loop->SetIdx(vertex_data.size() / 3);
            int num_of_he = loop->GetNum_of_he();
            auto *he = loop->getLedg();
            for( int i = 0; i < num_of_he; i ++) {
                vertex_data.push_back(he->getStart_v()->getPos()[0]);
                vertex_data.push_back(he->getStart_v()->getPos()[1]);
                vertex_data.push_back(he->getStart_v()->getPos()[2]);
                he = he->getNext_he();
            }
            loop = loop->getNext_l();
        }
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size() * sizeof(GLfloat), &vertex_data[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) (0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    VAOs.push_back(vao);
    VBOs.push_back(vbo);

}
