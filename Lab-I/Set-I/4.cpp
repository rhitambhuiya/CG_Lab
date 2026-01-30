#include <GL/glut.h>

void init()
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 300, 0, 300);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 0);
    glLineWidth(2);

    glBegin(GL_LINE_LOOP);
        glVertex2i(150, 250); // top
        glVertex2i(180, 170);
        glVertex2i(260, 170);
        glVertex2i(200, 120);
        glVertex2i(220, 40);
        glVertex2i(150, 90);
        glVertex2i(80, 40);
        glVertex2i(100, 120);
        glVertex2i(40, 170);
        glVertex2i(120, 170);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Simple Star");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

