#include <GL/glut.h>
#include <cmath>
#include <iostream>

// Colors: Red for fill, White for target (background)
float fillCol[3] = {1.0, 0.0, 0.0}; 
float oldCol[3] = {0.0, 0.0, 0.0}; 

bool isSameColor(float c1[3], float c2[3]) {
    return (std::abs(c1[0] - c2[0]) < 0.01f && 
            std::abs(c1[1] - c2[1]) < 0.01f && 
            std::abs(c1[2] - c2[2]) < 0.01f);
}

void floodFill8(int x, int y) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    // If the current pixel is the OLD color (the background), replace it
    if (isSameColor(currentColor, oldCol)) {
        
        // 1. Color the pixel
        glBegin(GL_POINTS);
            glColor3fv(fillCol);
            glVertex2i(x, y);
        glEnd();
        glFlush(); // Updates the screen so recursion sees the change

        // 2. 8-Connected calls
        floodFill8(x + 1, y);
        floodFill8(x - 1, y);
        floodFill8(x, y + 1);
        floodFill8(x, y - 1);
        floodFill8(x + 1, y + 1);
        floodFill8(x - 1, y - 1);
        floodFill8(x + 1, y - 1);
        floodFill8(x - 1, y + 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a black boundary (The algorithm will fill until it hits this)
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_POLYGON);
        glVertex2i(150, 150);
        glVertex2i(250, 150);
        glVertex2i(250, 250);
        glVertex2i(150, 250);
    glEnd();
    glFlush();

    // Start filling from the center
    // It will replace WHITE (oldCol) with RED (fillCol)
    floodFill8(200, 200);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Background is White
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("8-Connected Flood Fill");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
