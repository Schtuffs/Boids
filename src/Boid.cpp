#include "Boid.h"

#include <cmath>
#include <print>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Colour.h"
#include "Library.h"
#include "RenderManager.h"

GLuint Boid::s_shader = 0;
uint64_t s_totalBoids = 0;

// ----- Creation ----- Destruction -----

Boid::Boid(int width, int height) : Renderable(), m_x(rand() % width), m_y(rand() % height) {
    RenderManager::init();
    s_totalBoids++;
    if (s_shader == 0) {
        s_shader = RenderManager::createShader("../lib/default.vert", "../lib/default.frag");
    }
    m_colour = Colour(rand() % 255, rand() % 255, rand() % 255);
    m_velX = (rand() % 100) - 50;
    m_velY = (rand() % 100) - 50;
    normalize(BOID_MAGNITUDE);
    m_lambda = [&]() {
        render();
    };
}

Boid::Boid(double x, double y, double velX, double velY) : Renderable(), m_x(x), m_y(y), m_velX(velX), m_velY(velY) {
    RenderManager::init();
    s_totalBoids++;
    if (s_shader == 0) {
        s_shader = RenderManager::createShader("../lib/default.vert", "../lib/default.frag");
    }
    m_colour = Colour(rand() % 255, rand() % 255, rand() % 255);
    normalize(BOID_MAGNITUDE);
    m_lambda = [&](){
        render();
    };
}

Boid::~Boid() {
    RenderManager::terminate();
    s_totalBoids--;
    if (s_totalBoids == 0) {
        RenderManager::destroyShader(s_shader);
    }
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
        m_x = Window::DEFAULT_WINDOW_WIDTH + BOID_WIDTH;
    }
    // Right
    else if (m_x + m_velX > Window::DEFAULT_WINDOW_WIDTH + BOID_WIDTH) {
        m_x = -BOID_WIDTH;
    }
    // Up
    if (m_y + m_velY < (-BOID_HEIGHT)) {
        m_y = Window::DEFAULT_WINDOW_HEIGHT + BOID_HEIGHT;
    }
    // Down
    else if (m_y  + m_velY > Window::DEFAULT_WINDOW_HEIGHT + BOID_HEIGHT) {
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
    GLfloat fx = Library::map(m_x, 0, Window::DEFAULT_WINDOW_WIDTH, -1, 1);
    GLfloat fy = Library::map(m_y, 0, Window::DEFAULT_WINDOW_HEIGHT, -1, 1);
    GLfloat fw = Library::map(BOID_WIDTH  / 2, 0, Window::DEFAULT_WINDOW_WIDTH, 0, 2);
    GLfloat fh = Library::map(BOID_HEIGHT / 2, 0, Window::DEFAULT_WINDOW_HEIGHT, 0, 2);
    
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
        x1, y1,   (GLfloat)m_colour.r / Colour::MAX, (GLfloat)m_colour.g / Colour::MAX, (GLfloat)m_colour.b / Colour::MAX, (GLfloat)m_colour.a / Colour::MAX,
        x2, y2,   (GLfloat)m_colour.r / Colour::MAX, (GLfloat)m_colour.g / Colour::MAX, (GLfloat)m_colour.b / Colour::MAX, (GLfloat)m_colour.a / Colour::MAX,
        x3, y3,   (GLfloat)m_colour.r / Colour::MAX, (GLfloat)m_colour.g / Colour::MAX, (GLfloat)m_colour.b / Colour::MAX, (GLfloat)m_colour.a / Colour::MAX,
    };

    GLuint indices[] = {0, 1, 2};

    // Binding
    RenderManager::bindVAO(m_vao);
    RenderManager::bindVBO(m_vbo, vertices, sizeof(vertices));
    RenderManager::bindEBO(m_ebo, indices, sizeof(indices));
    
    // Editing
    RenderManager::linkAttrib(0, 2, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
    RenderManager::linkAttrib(1, 4, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    
    // Rendering
    RenderManager::bindShader(s_shader);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    RenderManager::unbindAll();
}

