#include <GL/glut.h>

// Translation values
float tx = 2.0f, ty = 0.0f, tz = 0.0f;

// Function to draw cube
void drawCube() {
    glutWireCube(1.0);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Simple camera (no perspective distortion effect here)
    gluLookAt(4, 4, 6,
              0, 0, 0,
              0, 1, 0);

    // ---- Original Cube ----
    glColor3f(1.0, 0.0, 0.0); // Red
    drawCube();

    // ---- Translated Cube ----
    glPushMatrix();
        glTranslatef(tx, ty, tz); // Move sideways only
        glColor3f(0.0, 1.0, 0.0); // Green
        drawCube();
    glPopMatrix();

    glutSwapBuffers();
}

// Initialization
void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    // ---- ORTHOGRAPHIC PROJECTION ----
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5, 5, -5, 10);

    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("3D Translation of Cube");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}