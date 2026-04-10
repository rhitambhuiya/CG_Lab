#include <GL/glut.h>
#include <bits/stdc++.h>
#define PI 3.141592

using namespace std;

int radius;
int xc, yc;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void input()
{
    cout << "Enter the radius of the circle: ";
    cin >> radius;
    cout << "Enter the center coordinate: ";
    cin >> xc >> yc;
}

void draw_Circle_Easy(int xc, int yc, int radius)
{
    int n = 1000;
    for(int i = 0; i <= n; i++)
    {
        float angle = (2.0 * PI * i) / n;
        float x = xc + radius * cos(angle);
        float y = yc + radius * sin(angle);
        glVertex2f(x, y);
    }
}

void draw_Circle_Algorithm(int xc, int yc, int radius)
{
    int x = 0, y = radius;
    int p = 1 - radius;
    while(x <= y)
    {
        glVertex2i(x + xc, y + yc);
        glVertex2i(x + xc, -y + yc);
        glVertex2i(-x + xc, y + yc);
        glVertex2i(-x + xc, -y + yc);
        glVertex2i(y + xc, x + yc);
        glVertex2i(-y + xc, x + yc);
        glVertex2i(-y + xc, -x + yc);
        glVertex2i(y + xc, -x + yc);
        if(p < 0)
        {
            x += 1;
            p += 1 + 2 * x;
        }
        else
        {
            x += 1;
            y -= 1;
            p += 1 + 2 * x - 2 * y;
        }
    }

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    draw_Circle_Algorithm(xc, yc, radius);
    glEnd();
    glFlush();
    // glLineWidth(2.0);
    // glBegin(GL_LINE_STRIP);
    // draw_Circle_Easy(xc, yc, radius);
    // glEnd();
    // glFlush();
}


int main(int argc, char **argv)
{
    input();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}