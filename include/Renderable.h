#pragma once

#include <iostream>

#include <glad/glad.h>

class Renderable {
public:
    virtual void render() = 0;
    virtual ~Renderable() = default;
    void init(const std::string& vertFile = "", const std::string& fragTexFile = "", const std::string& fragColFile = "");
    void terminate();

    // Helpful bind functions
    void bindColourShader();
    void bindTextureShader();
    void bindVAO();
    void bindVBO(GLfloat* vertices, GLsizeiptr size);
    void bindEBO(GLuint* indices, GLsizeiptr size);
    void bindTex(GLuint tex);
    void linkAttrib(GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset);

    void unbindShader();
    void unbindVAO();
    void unbindVBO();
    void unbindEBO();
    void unbindTex();
    void unbindAll();

protected:
    GLuint m_vao, m_vbo, m_ebo;
    
private:
    static GLuint s_shaderTexture, s_shaderColour;
    
    void readPrograms(const std::string& vertFile, const std::string& fragTexFile, const std::string& fragColFile);
};

