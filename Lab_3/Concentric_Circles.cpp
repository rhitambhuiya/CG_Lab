#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}

void drawCircle(int X, int Y, int radius)
{
    int p = 1 - radius;
    int x = 0, y = radius;
    
    while(x <= y)
    {
    	// 8 symmetric points
    	glVertex2i( x + X,  y + Y);
    	glVertex2i( y + X,  x + Y);
    	glVertex2i(-x + X,  y + Y);
    	glVertex2i(-y + X,  x + Y);
    	glVertex2i(-x + X, -y + Y);
    	glVertex2i(-y + X, -x + Y);
    	glVertex2i( x + X, -y + Y);
    	glVertex2i( y + X, -x + Y);

    	x++;

    	if (p < 0)
        	p += 1 + 2 * x;
    	else
    	{
        	y--;
        	p += 1 + 2 * x - 2 * y;
        }
    }
} 

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    int xc = 0, yc = 0;
   
    glColor3f(0.0, 1.0, 1.0);
    drawCircle(xc, yc, 70);
    
    glColor3f(1.0, 0.0, 1.0);
    drawCircle(xc, yc, 50);
    
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(xc, yc, 40);
    
    glColor3f(0.0, 0.0, 1.0);
    drawCircle(xc, yc, 25);

    glEnd();
    glFlush();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle at Origin");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
