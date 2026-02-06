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

    double dy = Y2 - Y1;
    double dx = x2 - x1;
    double slope = (dy * 1.0 / dx);
    
    double p = (2 * dy) - dx;
    double x = x1;
    double y = Y1;
    glBegin(GL_POINTS);
    while(x <= x2)
    {
    	glVertex2i(x, y);
    	if(p < 0)
    	{
    		p += 2 * dy;
    	}
    	else
    	{
    		y += 1;
    		p += 2 * dy - 2 * dx;
    	}
    	x += 1;
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
    glutCreateWindow("Bresenham");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

