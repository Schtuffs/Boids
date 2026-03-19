#include "Renderable.h"

#include <fstream>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static uint64_t s_totalInits = 0;
GLuint Renderable::s_shaderColour = 0, Renderable::s_shaderTexture = 0;

std::string read(const std::string& filename) {
    // Create file
    std::ifstream in(filename, std::ios::binary);
	if (!in.is_open()) {
		throw 1;
	}

	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();
	return contents;
}

// Returns original ID or 0 based on success
GLuint compileErrors(GLuint id, GLuint type) {
    char error[1024];
    GLsizei read;
    GLint status = GL_TRUE;
    
    // For the vertex and fragment shaders
    glGetShaderiv(id, type, &status);
    if (status != GL_TRUE) {
        if (type == GL_COMPILE_STATUS) {
            glGetShaderInfoLog(id, 1024, &read, error);
        }
        else {
            glGetProgramInfoLog(id, 1024, &read, error);
        }

        std::println(stderr, "COMPILE ERROR: {}", error);
        return 0;
    }
    return id;
}

GLuint readProgram(const std::string& file, GLuint shaderType) {
    std::string code;
    try {
        code = read(file);
    } catch (int e) {
        std::println(stderr, "ERROR: Could not read file: {}", file);
        return 0;
    }

    // Compile shader
    const char* source = code.c_str();
    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);
    return compileErrors(shaderID, GL_COMPILE_STATUS);
}

void Renderable::readPrograms(const std::string& vertFile, const std::string& fragTexFile, const std::string& fragColFile) {
    GLuint vertShader = readProgram(vertFile, GL_VERTEX_SHADER);
    GLuint fragTexShader = readProgram(fragTexFile, GL_FRAGMENT_SHADER);
    GLuint fragColShader = readProgram(fragColFile, GL_FRAGMENT_SHADER);
    
    // Bind the shaders to the colour shading program
    if (vertShader && fragColShader) {
        s_shaderColour = glCreateProgram();
        glAttachShader(s_shaderColour, vertShader);
        glAttachShader(s_shaderColour, fragColShader);
        glLinkProgram(s_shaderColour);
        compileErrors(s_shaderColour, GL_LINK_STATUS);
    }
    
    // Bind the shaders to the texture shading program
    if (vertShader && fragTexShader) {
        s_shaderTexture = glCreateProgram();
        glAttachShader(s_shaderTexture, vertShader);
        glAttachShader(s_shaderTexture, fragTexShader);
        glLinkProgram(s_shaderTexture);
        compileErrors(s_shaderTexture, GL_LINK_STATUS);
    }

    if (vertShader) {
        glDeleteShader(vertShader);
    }
    if (fragColShader) {
        glDeleteShader(fragColShader);
    }
    if (fragTexShader) {
        glDeleteShader(fragTexShader);
    }
}

void Renderable::init(const std::string& vertFile, const std::string& fragTexFile, const std::string& fragColFile) {
    // Read files
    if (s_totalInits == 0) {
        readPrograms(vertFile, fragTexFile, fragColFile);
    }
    
    // Allows for initialization and termination
    s_totalInits++;
    
    // Create VAO for own renderings
    glGenVertexArrays(1, &m_vao);

    // Create EBO for own renderings
    glGenBuffers(1, &m_vbo);

    // Create VBO for drawing board
    glGenBuffers(1, &m_ebo);
}

void Renderable::terminate() {
    s_totalInits--;
    if (s_totalInits == 0) {
        // Deletes programs
        glDeleteProgram(s_shaderColour);
        glDeleteProgram(s_shaderTexture);
    }

    glDeleteVertexArrays(1, &this->m_vao);
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteBuffers(1, &this->m_ebo);
}



void Renderable::bindColourShader() {
    glUseProgram(s_shaderColour);
}

void Renderable::bindTextureShader() {
    glUseProgram(s_shaderTexture);
}

void Renderable::bindVAO() {
    glBindVertexArray(m_vao);
}

void Renderable::bindVBO(GLfloat* vertices, GLsizeiptr size) {
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW);
}

void Renderable::bindEBO(GLuint* indices, GLsizeiptr size) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void Renderable::bindTex(GLuint tex) {
    glBindTexture(GL_TEXTURE_2D, tex);
}

void Renderable::linkAttrib(GLuint layout, GLuint components, GLenum type, GLsizeiptr stride, void* offset) {
    glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
}

// Unbinding

void Renderable::unbindShader() {
    glUseProgram(0);
}

void Renderable::unbindVAO() {
    glBindVertexArray(0);
}

void Renderable::unbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderable::unbindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderable::unbindTex() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderable::unbindAll() {
    unbindShader();
    unbindVAO();
    unbindVBO();
    unbindEBO();
    unbindTex();
}

