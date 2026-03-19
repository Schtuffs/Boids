#include "Boid.h"

#include <cmath>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Defines.h"
#include "Colour.h"
#include "Library.h"

// ----- Creation ----- Destruction -----

Boid::Boid(int width, int height) : m_x(rand() % width), m_y(rand() % height) {
    Renderable::init("../lib/default.vert", "../lib/defaultTex.frag", "../lib/defaultCol.frag");
    m_colour = Colour(rand() % 255, rand() % 255, rand() % 255);
    m_velX = (rand() % 100) - 50;
    m_velY = (rand() % 100) - 50;
    // m_velX = 0;
    // m_velY = -10;
    normalize(BOID_MAGNITUDE);
}

Boid::Boid(double x, double y, double velX, double velY) : m_x(x), m_y(y), m_velX(velX), m_velY(velY) {
    Renderable::init("../lib/default.vert", "../lib/defaultTex.frag", "../lib/defaultCol.frag");
    m_colour = Colour(rand() % 255, rand() % 255, rand() % 255);
    normalize(BOID_MAGNITUDE);
}

Boid::~Boid() {
    Renderable::terminate();
}



// ----- Update -----

void Boid::normalize(double magnitude) {
    double vector = std::sqrt((m_velX * m_velX) + (m_velY * m_velY));
    m_velX = (m_velX / vector) * magnitude;
    m_velY = (m_velY / vector) * magnitude;
}

void Boid::checkEdges() {
    // Left
    if (m_x + m_velX < (-BOID_WIDTH)) {
        m_x = WINDOW_SIZE_X + BOID_WIDTH;
    }
    // Right
    else if (m_x + m_velX > WINDOW_SIZE_X + BOID_WIDTH) {
        m_x = -BOID_WIDTH;
    }
    // Up
    if (m_y + m_velY < (-BOID_HEIGHT)) {
        m_y = WINDOW_SIZE_Y + BOID_HEIGHT;
    }
    // Down
    else if (m_y  + m_velY > WINDOW_SIZE_Y + BOID_HEIGHT) {
        m_y = -BOID_HEIGHT;
    }
}

void Boid::update() {
    // Check edges
    checkEdges();
    
    // Add velocity
    m_x +=m_velX;
    m_y +=m_velY;
}

void Boid::render() {
    // Update before render
    update();
    
    // Calculating where the points are in vector-space instead of pixel-space
    GLfloat fx = Library::map(m_x, 0, WINDOW_SIZE_X, -1, 1);
    GLfloat fy = Library::map(m_y, 0, WINDOW_SIZE_Y, -1, 1);
    GLfloat fw = Library::map(BOID_WIDTH  / 2, 0, WINDOW_SIZE_X, 0, 2);
    GLfloat fh = Library::map(BOID_HEIGHT / 2, 0, WINDOW_SIZE_Y, 0, 2);
    
    // Calculate boid angles
    double theta = std::atan2(m_velY, m_velX);
    GLfloat x1 = (fx) + ((fx + fw) - fx) * std::cos(theta) - ((fy + 00) - fy) * std::sin(theta);
    GLfloat y1 = (fy) + ((fx + fw) - fx) * std::sin(theta) + ((fy + 00) - fy) * std::cos(theta);
    GLfloat x2 = (fx) + ((fx - fw) - fx) * std::cos(theta) - ((fy - fh) - fy) * std::sin(theta);
    GLfloat y2 = (fy) + ((fx - fw) - fx) * std::sin(theta) + ((fy - fh) - fy) * std::cos(theta);
    GLfloat x3 = (fx) + ((fx - fw) - fx) * std::cos(theta) - ((fy + fh) - fy) * std::sin(theta);
    GLfloat y3 = (fy) + ((fx - fw) - fx) * std::sin(theta) + ((fy + fh) - fy) * std::cos(theta);

    // Places points into array for rendering
    GLfloat vertices[] = {
        // Coordinates      // Colours
        x1, y1,   m_colour.r / (GLfloat)255.0, m_colour.g / (GLfloat)255.0, m_colour.b / (GLfloat)255.0, m_colour.a / (GLfloat)255.0,
        x2, y2,   m_colour.r / (GLfloat)255.0, m_colour.g / (GLfloat)255.0, m_colour.b / (GLfloat)255.0, m_colour.a / (GLfloat)255.0,
        x3, y3,   m_colour.r / (GLfloat)255.0, m_colour.g / (GLfloat)255.0, m_colour.b / (GLfloat)255.0, m_colour.a / (GLfloat)255.0,
    };

    GLuint indices[] = {0, 1, 2};

    // Binding
    bindVAO();
    bindVBO(vertices, sizeof(vertices));
    bindEBO(indices, sizeof(indices));

    // Editing
    linkAttrib(0, 2, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
    linkAttrib(1, 4, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    // Unbind
    unbindAll();

    // Rendering
    Renderable::bindColourShader();
    bindVAO();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    unbindAll();
}

