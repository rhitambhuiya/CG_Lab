#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

int n;          // number of sides
float radius = 100.0f;

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glLineWidth(2);

    float cx = 250;   // center x
    float cy = 250;   // center y

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
    {
        float angle = 2 * M_PI * i / n;   // angle for each vertex
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    cout << "Enter number of sides: ";
    cin >> n;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Regular Polygon");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}

