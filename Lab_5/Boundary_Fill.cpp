#include <GL/glut.h>
#include <cmath>
#include <iostream>

float fillCol[3] = {1.0, 0.0, 0.0};  // Red
float borderCol[3] = {0.0, 0.0, 0.0}; // Black

// Helper to check colors with a small tolerance
bool isSameColor(float c1[3], float c2[3]) {
    return (std::abs(c1[0] - c2[0]) < 0.02f && 
            std::abs(c1[1] - c2[1]) < 0.02f && 
            std::abs(c1[2] - c2[2]) < 0.02f);
}

void boundaryFill8(int x, int y) {
    float interiorCol[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, interiorCol);

    // If NOT border AND NOT already red
    if (!isSameColor(interiorCol, borderCol) && !isSameColor(interiorCol, fillCol)) {
        
        // Color this pixel immediately so neighbors don't re-process it
        glBegin(GL_POINTS);
            glColor3fv(fillCol);
            glVertex2i(x, y);
        glEnd();
        glFlush(); 

        // 8-Connected directions
        boundaryFill8(x + 1, y);
        boundaryFill8(x - 1, y);
        boundaryFill8(x, y + 1);
        boundaryFill8(x, y - 1);
        boundaryFill8(x + 1, y + 1);
        boundaryFill8(x - 1, y - 1);
        boundaryFill8(x - 1, y + 1);
        boundaryFill8(x + 1, y - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // DRAW A WATER-TIGHT BOUNDARY
    glColor3fv(borderCol);
    glLineWidth(3); // Thicker line prevents 8-connected leakage
    glBegin(GL_LINE_LOOP);
        glVertex2i(150, 150);
        glVertex2i(250, 150);
        glVertex2i(250, 250);
        glVertex2i(150, 250);
    glEnd();
    glFlush(); 

    // START FILL
    // We use a small square (150 to 250) to avoid immediate stack overflow
    boundaryFill8(200, 200); 
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Use 1:1 pixel mapping for 500x500 window
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("8-Connected Boundary Fill");
    
    init();
    glutDisplayFunc(display);
    
    // IMPORTANT: Inform the user
    
    
    glutMainLoop();
    return 0;
}
