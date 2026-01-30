#include <GL/glut.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int x, d;
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void display()
{
	int points[3][2] = {{50, 100}, {75, 150}, {100, 200}};
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	int x0 = 0, y0 = 100;
	int factor = -1;
	glBegin(GL_LINE_STRIP);
	
	while(x0 <= x)
	{
		glVertex2i(x0, y0);
		x0 += 20;
		y0 = y0 + (50 * factor);
		factor *= -1;
	}
	
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the ending x co-ordinate, others will be handled by the programmer: ";
	cin >> x;
	
	float diff = (x - 0) / 20;
	if(diff != ceil(diff))
		return -1;
		
	d = (int)diff;
	if(d & 1)
		return -1;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Draw Line Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
} 
