#include <GL/glut.h>

void init()
{
    glClearColor(1, 1, 1, 1);        // white background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);      // 2D coordinate system
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0, 0, 0);              // black lines
    glLineWidth(2);

    // Ground line
    glBegin(GL_LINES);
        glVertex2i(0, 80);
        glVertex2i(500, 80);
    glEnd();

    // House body
    glBegin(GL_LINE_LOOP);
        glVertex2i(150, 80);
        glVertex2i(150, 250);
        glVertex2i(350, 250);
        glVertex2i(350, 80);
    glEnd();

    // Roof
    glBegin(GL_LINES);
        glVertex2i(150, 250);
        glVertex2i(250, 350);
        glVertex2i(250, 350);
        glVertex2i(350, 250);
    glEnd();

    // Door
    glBegin(GL_LINE_LOOP);
        glVertex2i(230, 80);
        glVertex2i(230, 160);
        glVertex2i(270, 160);
        glVertex2i(270, 80);
    glEnd();

    // Left window
    glBegin(GL_LINE_LOOP);
        glVertex2i(180, 170);
        glVertex2i(180, 210);
        glVertex2i(220, 210);
        glVertex2i(220, 170);
    glEnd();

    // Right window
    glBegin(GL_LINE_LOOP);
        glVertex2i(280, 170);
        glVertex2i(280, 210);
        glVertex2i(320, 210);
        glVertex2i(320, 170);
    glEnd();

    // Sun (points)
    glPointSize(5);
    glBegin(GL_POINTS);
        glVertex2i(430, 430);
        glVertex2i(440, 430);
        glVertex2i(420, 430);
        glVertex2i(430, 440);
        glVertex2i(430, 420);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Scene");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

