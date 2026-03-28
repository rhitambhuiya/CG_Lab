#include <GL/glut.h>

// Scaling factors
float sx = 1.5f, sy = 2.0f, sz = 1.0f;

// Draw pyramid with edges
void drawPyramid() {
    // Draw faces
    glBegin(GL_TRIANGLES);

    // Front
    glVertex3f(0,1,0);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);

    // Right
    glVertex3f(0,1,0);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);

    // Back
    glVertex3f(0,1,0);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);

    // Left
    glVertex3f(0,1,0);
    glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,1);

    glEnd();

    // Base
    glBegin(GL_QUADS);
    glVertex3f(-1,-1,1);
    glVertex3f(1,-1,1);
    glVertex3f(1,-1,-1);
    glVertex3f(-1,-1,-1);
    glEnd();

    // Draw edges (IMPORTANT for 3D look)
    glColor3f(0,0,0);
    glBegin(GL_LINES);

    // Apex to base corners
    glVertex3f(0,1,0); glVertex3f(-1,-1,1);
    glVertex3f(0,1,0); glVertex3f(1,-1,1);
    glVertex3f(0,1,0); glVertex3f(1,-1,-1);
    glVertex3f(0,1,0); glVertex3f(-1,-1,-1);

    // Base edges
    glVertex3f(-1,-1,1); glVertex3f(1,-1,1);
    glVertex3f(1,-1,1); glVertex3f(1,-1,-1);
    glVertex3f(1,-1,-1); glVertex3f(-1,-1,-1);
    glVertex3f(-1,-1,-1); glVertex3f(-1,-1,1);

    glEnd();
}

// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(5,5,8, 0,0,0, 0,1,0);

    // Original
    glColor3f(1,0,0);
    drawPyramid();

    // Scaled
    glPushMatrix();
        glTranslatef(3,0,0);
        glScalef(sx, sy, sz);
        glColor3f(0,1,0);
        drawPyramid();
    glPopMatrix();

    glutSwapBuffers();
}

// Init
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(1,1,1,1); // White background helps visibility

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,1,100);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("3D Pyramid Scaling");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
