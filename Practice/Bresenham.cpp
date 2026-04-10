#include <GL/glut.h>
#include <iostream>

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 250, 0, 250);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(2.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    int X1 = 50, Y1 = 50;
    int X2 = 200, Y2 = 200;

    int dy = Y2 - Y1, dx = X2 - X1;
    int p = 2 * dy - dx;
    while(X1 <= X2)
    {
        glVertex2i(X1, Y1);
        X1 += 1;
        if(p >= 0)
        {
            p += 2 * dy - dx;
            Y1 += 1;
        }
        else
            p += 2 * dy;
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(250, 250);
    glutCreateWindow("Bresenham");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}