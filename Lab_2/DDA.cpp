#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

double x1 = 0.0, Y1 = 0.0;
double x2 = 0.0, Y2 = 0.0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void input()
{
    cout << "Enter the coordinates of the first point: ";
    cin >> x1 >> Y1;
    cout << "Enter the coordinates of the second point: ";
    cin >> x2 >> Y2;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    glPointSize(2.0);

    double x = x1;
    double y = Y1;

    double dx = x2 - x1;
    double dy = Y2 - Y1;

    double slope = fabs(dy / dx);

    int xStep = (dx >= 0) ? 1 : -1;
    int yStep = (dy >= 0) ? 1 : -1;

    glBegin(GL_POINTS);

    if (slope <= 1)
    {
        while ((xStep > 0 && x <= x2) || (xStep < 0 && x >= x2))
        {
            glVertex2i((int)round(x), (int)round(y));
            x += xStep;
            y += slope * yStep;
        }
    }
    else
    {
        while ((yStep > 0 && y <= Y2) || (yStep < 0 && y >= Y2))
        {
            glVertex2i((int)round(x), (int)round(y));
            y += yStep;
            x += (1.0 / slope) * xStep;
        }
    }

    glEnd();
    glFlush();
}


int main(int argc, char **argv)
{
    input();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Draw Line Using Points");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

