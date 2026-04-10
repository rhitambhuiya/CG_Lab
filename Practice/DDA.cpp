#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

float X1, Y1, X2, Y2;

void init()
{
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void input()
{
    cout << endl << "Enter the coordinates of the first point: ";
    cin >> X1 >> Y1;
    cout << endl << "Enter the coordinates of the second point: ";
    cin >> X2 >> Y2;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float x = X1;  
    float y = Y1;

    float dx = X2 - X1;
    float dy = Y2 - Y1;

    glPointSize(1.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);

    if (dx == 0) //vertical line
    {
       while(y <= Y2)
        {
            glVertex2f(x, y);
            y += 1;
        }
    }
    else
    {
        float m = dy / dx;
        int factor = 1;
        if(m < 0)
            factor = -1;

        m = fabs(m);

        if (m <= 1)
        {
            while (x <= X2)
            {
                glVertex2f(x, y);
                x += 1;
                y += m * factor;
            }
        }
        else
        {
            while (x <= X2)
            {
                glVertex2f(x, y);
                y += factor;
                x += (1.0 / m);
            }
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
    glutCreateWindow("DDA");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}