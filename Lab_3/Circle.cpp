#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

int radius;
int xc, yc;
vector<pair<int, int>> points;

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    glPointSize(2.0);
    int x = 0, y = radius;
    int p = 1 - radius;
    
    glBegin(GL_POINTS);
    
    //Plotting the 1st octant
    while(x <= y)
    {
    	// 8 symmetric points
    	glVertex2i( x + xc,  y + yc);
    	glVertex2i( y + xc,  x + yc);
    	glVertex2i(-x + xc,  y + yc);
    	glVertex2i(-y + xc,  x + yc);
    	glVertex2i(-x + xc, -y + yc);
    	glVertex2i(-y + xc, -x + yc);
    	glVertex2i( x + xc, -y + yc);
    	glVertex2i( y + xc, -x + yc);

    	x++;

    	if (p < 0)
        	p += 1 + 2 * x;
    	else
    	{
        	y--;
        	p += 1 + 2 * x - 2 * y;
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
    glutCreateWindow("Circle at Origin");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
