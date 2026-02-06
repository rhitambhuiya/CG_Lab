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
    int count = 0;
    bool flag = true; // true is for dotted, false is for dashed
    int dot_counter = 5;
    int dash_counter = 15;
    
    glBegin(GL_POINTS);
    while(x <= x2)
    {
    	if(dot_counter > 0) {
    		if(count == 0)
    		{
    			glVertex2i(x, y);
    			count = 5;
    			dot_counter -= 1;
    			if(!dot_counter)
    				dash_counter = 15;
    		}	
    		count--;
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
    	else
    	{
    		glVertex2i(x, y);
    		dash_counter -= 1;
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
    		if(!dash_counter)
    			dot_counter = 5;
    		
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
    glutCreateWindow("Dashed-Dotted Line");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

