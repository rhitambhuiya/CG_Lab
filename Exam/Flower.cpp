#include <GL/glut.h>
#include <bits/stdc++.h>
#include <cmath>
#define PI 3.141592


float b_col[3] = {0.0, 0.0, 0.0};

int xmin = 30, xmax = 500;
int ymin = 30, ymax = 500;

int top = 8;
int down = 4;
int right = 2;
int left = 1;

bool isSameColor(float c1[3], float c2[3])
{
	return (c1[0] == c2[0] and c1[1] == c2[1] and c1[2] == c2[2]);
}

int getCode(float x, float y)
{
	int code = 0;
	if(x < xmin)
		code |= left;
	else if(x > xmax)
		code |= right;
		
	if(y < ymin)
		code |= down;
	else if(y > ymax)
		code |= top;
		
	return code;
}

void clipping(float X1, float Y1, float X2, float Y2)
{
	bool accept = false;
	float x, y;
	float m = (Y2 - Y1) * 1.0 / (X2 - X1);
	float c = Y1 - (m * X1);
	
	while(true)
	{
		int code1 = getCode(X1, Y1);
		int code2 = getCode(X2, Y2);
		
		if(code1 == 0 and code2 == 0)
		{
			accept = true;
			break;
		}
		
		if(code1 & code2)
			break;
			
		int codeOut = code1 ? code1 : code2;
		
		if(codeOut & left)
		{
			x = xmin;
			y = m * x + c;
		}
		
		else if(codeOut & right)
		{
			x = xmax;
			y = m * x + c;
		}
		
		else if(codeOut & top)
		{
			y = ymax;
			x = (y - c) / m;
		}
		
		else if(codeOut & down)
		{
			y = ymin;
			x = (y - c) / m;
		}
		
		if(codeOut == code1)
		{
			X1 = x;
			Y1 = y;
		}
		else
		{
			X2 = x;
			Y2 = y;
		}
	}
	
	if(accept)
	{
		glColor3f(1, 1, 1);
		glBegin(GL_LINE_STRIP);
		glVertex2i(X1, Y1);
		glVertex2i(X2, Y2);
		glEnd();
	}
}

void boundaryFill(int x, int y, float f_col[3])
{
	float cur_col[3];
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, cur_col);
	
	if(isSameColor(cur_col, b_col) or isSameColor(cur_col, f_col))
		return;
		
	glPointSize(1.0);
	glColor3fv(f_col);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
	
	boundaryFill(x - 1, y, f_col);
	boundaryFill(x, y - 1, f_col);
	boundaryFill(x + 1, y, f_col);
	boundaryFill(x, y + 1, f_col);
}

void init()
{
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 600);
}

void drawCircle(float cx, float cy, float r)
{
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	int points = 200;
	for(int i = 0; i < points; i++)
	{
		float angle = (2.0 * i * PI) / points;
		float x = cx + r * cos(angle);
		float y = cy + r * sin(angle);
		glVertex2f(x, y);
	}
	float x = 0, y = r;
	glEnd();
	glBegin(GL_POINTS);
	
	glVertex2f(x + cx, y + cy);
	glVertex2f(-x + cx, y + cy);
	glVertex2f(x + cx, -y + cy);
	glVertex2f(-x + cx, -y + cy);
	glVertex2f(y + cx, -x + cy);
	glVertex2f(-y + cx, x + cy);
	glVertex2f(-y + cx, -x + cy);
	glVertex2f(y + cx, x + cy);
	
	glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry)
{
	glLineWidth(3.0);
	glBegin(GL_LINE_LOOP);
	int points = 200;
	for(int i = 0; i < points; i++)
	{
		float angle = (2.0 * i * PI) / points;
		float x = cx + rx * cos(angle);
		float y = cy + ry * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawPetals()
{
	glColor3f(0, 0, 0);
	drawEllipse(250, 375, 35, 75);
	drawEllipse(250, 125, 35, 75);
	drawEllipse(125, 250, 75, 35);
	drawEllipse(375, 250, 75, 35);
}

void drawFlower()
{
	glColor3f(0, 0, 0);
	drawCircle(250, 250, 50);
}

void drawSun()
{
	glColor3f(0, 0, 0);
	drawEllipse(450, 450, 30, 30);
	glBegin(GL_LINE_STRIP);
	glVertex2i(450, 480);
	glVertex2i(450, 530);
	glEnd();
	clipping(450, 480, 480, 530);
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2i(450, 500);
	glVertex2i(450, 530);
	glEnd();
	
	
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(480, 450);
	glVertex2i(530, 450);
	glEnd();
	clipping(450, 480, 480, 530);
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	glVertex2i(500, 450);
	glVertex2i(530, 450);
	glEnd();
	
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(450, 420);
	glVertex2i(450, 380);
	glEnd();
	
}

void drawWindow()
{
	glLineWidth(3.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(xmin, ymin);
	glVertex2i(xmax, ymin);
	glVertex2i(xmax, ymax);
	glVertex2i(xmin, ymax);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawFlower();
	drawPetals();
	drawWindow();
	drawSun();
	
	float f_col[3] = {1.0, 0.0, 0.0};
	boundaryFill(250, 250, f_col);
	
	f_col[1] = 1.0;
	boundaryFill(250, 375, f_col);
	boundaryFill(250, 125, f_col);
	boundaryFill(125, 250, f_col);
	boundaryFill(375, 250, f_col);
	boundaryFill(450, 450, f_col);
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Flower Scene");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
