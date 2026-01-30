#include <GL/glut.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int n;
vector<pair<int, int>> points;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_LINE_STRIP);
	
	for(int i = 0; i < n; i++)
	{
		glVertex2i(points[i].first, points[i].second);
	}
	
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "Enter the number of points: ";
	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		cout << endl << "Enter the point " << (i + 1) << ": ";
		int a, b;
		cin >> a >> b;
		points.push_back({a, b});
	}	
	
	points.push_back(points[0]);
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Draw Line Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
