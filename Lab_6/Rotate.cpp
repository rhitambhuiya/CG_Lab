#include <GL/glut.h>

// Rotation angle
float angle = 45.0f;

// Function to draw cube
void drawCube()
{
    glutWireCube(3.0);
}

// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Camera setup
    gluLookAt(6, 6, 10, 0, 0, 0, 0, 1, 0);

    // 🔵 Original Cube
    glPushMatrix();
        glTranslatef(-3, 0, 0);   // Move left
        glColor3f(0, 0, 1);
        drawCube();
    glPopMatrix();

    // 🔴 Rotated Cube (about X-axis)
    glPushMatrix();
        glTranslatef(3, 0, 0);    // Move right
        glRotatef(angle, 1.0, 0.0, 0.0); // Rotation about X-axis
        glColor3f(1, 0, 0);
        drawCube();
    glPopMatrix();

    glutSwapBuffers();
}

// Initialization
void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    // Smooth out the lines
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    
    // Make lines beefier
    glLineWidth(1.5); 
}

// Reshape function
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)w/h, 1, 50);

    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Rotation about X-axis");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
