#include <GL/glut.h>
#include <cmath>
#include <iostream>

float fillColor[3] = {1.0, 0.0, 0.0};  // Red
float borderColor[3] = {0, 0, 0}; // Black

bool isSameColor(float c1[3], float c2[3]) {
    return (c1[0] == c2[0] and c1[1] == c2[1] and c1[2] == c2[2]);
}

void boundaryFill(int x, int y) {
    float currColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currColor);

    if (!isSameColor(currColor, borderColor) and !isSameColor(currColor, fillColor)){

    glBegin(GL_POINTS);
    glColor3fv(fillColor);
    glVertex2i(x, y);
    glEnd();
    glFlush(); 
    boundaryFill(x - 2, y);
    boundaryFill(x, y - 2);
    boundaryFill(x + 2, y);
    boundaryFill(x, y + 2);}
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(borderColor);
    glLineWidth(5.0); 
    glBegin(GL_LINE_LOOP);
        glVertex2i(150, 150);
        glVertex2i(250, 150);
        glVertex2i(250, 250);
        glVertex2i(150, 250);
    glEnd();
    glFlush(); 
    glPointSize(2.0);
    boundaryFill(200, 200); 
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); 
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("8-Connected Boundary Fill");
    
    init();
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}
