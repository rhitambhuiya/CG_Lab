#include <GL/glut.h>
#include <cmath>
#include <iostream>

float fillCol[3] = {1.0, 1.0, 0.0}; 
float oldCol[3] = {1.0, 0.0, 0.0}; 

bool isSameColor(float c1[3], float c2[3]) {
    return (std::abs(c1[0] - c2[0]) < 0.01f && 
            std::abs(c1[1] - c2[1]) < 0.01f && 
            std::abs(c1[2] - c2[2]) < 0.01f);
}

void floodFill8(int x, int y) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    
    if (isSameColor(currentColor, oldCol)) {
        
        glBegin(GL_POINTS);
            glColor3fv(fillCol);
            glVertex2i(x, y);
        glEnd();
        glFlush(); 

        floodFill8(x + 2, y);
        floodFill8(x - 2, y);
        floodFill8(x, y + 2);
        floodFill8(x, y - 2);
        floodFill8(x + 2, y + 2);
        floodFill8(x - 2, y - 2);
        floodFill8(x + 2, y - 2);
        floodFill8(x - 2, y + 2);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_POLYGON);
        glVertex2i(150, 150);
        glVertex2i(250, 150);
        glVertex2i(250, 250);
        glVertex2i(150, 250);
    glEnd();
    glFlush();
    glPointSize(2.0);
    floodFill8(200, 200);
}

void init() {
    glClearColor(1, 1, 1, 1); 
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