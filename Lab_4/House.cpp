#include <GL/glut.h>
#include <cmath>

// Function to draw a circle (used for sun)
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1416f * i / 100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Function to draw a house
void drawHouse(float x, float y) {
    // House base
    glColor3f(0.8f, 0.5f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 0.2f, y);
        glVertex2f(x + 0.2f, y + 0.2f);
        glVertex2f(x, y + 0.2f);
    glEnd();

    // Roof
    glColor3f(0.6f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 0.05f, y + 0.2f);
        glVertex2f(x + 0.25f, y + 0.2f);
        glVertex2f(x + 0.1f, y + 0.35f);
    glEnd();

    // Door
    glColor3f(0.4f, 0.2f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(x + 0.075f, y);
        glVertex2f(x + 0.125f, y);
        glVertex2f(x + 0.125f, y + 0.1f);
        glVertex2f(x + 0.075f, y + 0.1f);
    glEnd();
}

// Function to draw fence
void drawFence() {
    glColor3f(0.9f, 0.9f, 0.9f);

    for(float i = -1.0f; i <= 1.0f; i += 0.1f) {
        glBegin(GL_LINES);
            glVertex2f(i, -0.2f);
            glVertex2f(i, 0.0f);
        glEnd();
    }

    // Horizontal lines
    glBegin(GL_LINES);
        glVertex2f(-1.0f, -0.05f);
        glVertex2f(1.0f, -0.05f);

        glVertex2f(-1.0f, -0.15f);
        glVertex2f(1.0f, -0.15f);
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.7f, 0.7f, 0.15f);

    // Draw Houses
    drawHouse(-0.8f, -0.2f);
    drawHouse(-0.2f, -0.2f);
    drawHouse(0.4f, -0.2f);

    // Draw Fence
    drawFence();

    glFlush();
}

// Initialization
void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Sky blue background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3 Houses, Fence and Sun");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
