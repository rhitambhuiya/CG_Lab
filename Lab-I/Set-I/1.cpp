#include <GL/glut.h>

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void display()
{
	int points[3][2] = {{50, 100}, {75, 150}, {100, 200}};
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(3.0);
	glBegin(GL_LINE_STRIP);
	
	for(int i = 0; i < 3; i++)
	{
		glVertex2iv(points[i]);
	}
	
	glEnd();
	glFlush();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Draw Line Example");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
