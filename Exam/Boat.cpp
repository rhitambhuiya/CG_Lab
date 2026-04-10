#include <GL/glut.h>
#include <bits/stdc++.h>
#include <cmath>
#define PI 3.141592

using namespace std;

void init()
{
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

void transform(float x, float y)
{
	float angle = 30.0;
	angle *= PI / 180.0;
	
	int tx = 75, ty = 75;
	
	float x_new  = x * cos(angle) + y * sin(angle);
	float y_new = y * cos(angle) - x * sin(angle);
	
	glVertex2f(x_new + tx, y_new + ty);
}

void DDA(float X1, float Y1, float X2, float Y2, bool flag)
{
	float m = (Y2 - Y1) * 1.0 / (X2 - X1);
	int factor = 1;
	if(m < 0)
		factor = -1;
	m = fabs(m);
	
	float x = X1;
	float y = Y1;
	
	while(x <= X2)
	{
		if(flag)
			glColor3f(0, 0, 0);
		else
			glColor3f(0, 0, 1);
		glVertex2f(x, y);
		
		glColor3f(1, 0, 0);
		if(flag)
			transform(x, y);
		if(m <= 1)
		{
			x += 1;
			y += m * factor;
		} 
		else
		{
			x += 1.0 / m;
			y += factor;
		}
	}
}

void drawFlag()
{
	glLineWidth(3.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(150, 300);
	glVertex2i(250, 300);
	glVertex2i(200, 350);
	glEnd();
	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	transform(150, 300);
	transform(250, 300);
	transform(200, 350);
	glEnd();
}

void Bresenham(int X1, int Y1, int X2, int Y2, bool flag)
{
	int dy = Y2 - Y1;
	int dx = X2 - X1;
	
	int p = 2 * dy - dx;
	int x = X1;
	int y = Y1;
	
	while(x <= X2)
	{	
		if(flag)
			glColor3f(0, 0, 0);
		else
			glColor3f(0, 0, 1);
		glVertex2i(x, y);
		glColor3f(1, 0, 0);
		if(flag)
			transform(x, y);
		x += 1;
		if(p < 0)
			p += 2 * dy;
		else
		{
			y += 1;
			p += 2 * dy - 2 * dx;
		}
	}
}

void drawBoat()
{
	glPointSize(2.0);
	glBegin(GL_POINTS);
	DDA(250, 252, 300, 300, true);
	glEnd();
	glBegin(GL_POINTS);
	Bresenham(150, 252, 250, 252, true);
	glEnd();
	glBegin(GL_POINTS);
	DDA(100, 300, 150, 252, true);
	glEnd();
	glBegin(GL_POINTS);
	Bresenham(100, 300, 300, 300, true);
	glEnd();
}

void drawWater()
{
	glPointSize(2.0);
	glBegin(GL_POINTS);
	DDA(0, 250, 500, 250, false);
	glEnd();
	glBegin(GL_POINTS);
	DDA(0, 225, 500, 225, false);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawWater();
	drawBoat();
	drawFlag();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Boat Scene");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
