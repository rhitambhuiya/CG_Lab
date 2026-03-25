#include <GL/glut.h>
#include <cmath>

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-15, 15, -15, 15);
}

void drawVector(float x, float y)
{
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(x, y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 🟢 Original vector
    glColor3f(0.0, 1.0, 0.0);
    drawVector(0.0, 10.0);

    // 🔴 Rotated vector (30 degrees)
    glPushMatrix();
    glRotatef(30.0, 0.0, 0.0, 1.0);  // rotate about Z-axis
    glColor3f(1.0, 0.0, 0.0);
    drawVector(0.0, 10.0);
    glPopMatrix();

    // 🔵 Translated + Rotated vector
    glPushMatrix();
    glTranslatef(3.0, 2.0, 0.0);     // move first
    glRotatef(30.0, 0.0, 0.0, 1.0);  // then rotate
    glColor3f(0.0, 0.0, 1.0);
    drawVector(0.0, 10.0);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rotation and Translation using Matrix");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
