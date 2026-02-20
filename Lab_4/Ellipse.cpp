#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int radius_x, radius_y;
int xc, yc;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

void input()
{
    cout << "Enter the x-radius of the circle: ";
    cin >> radius_x;
    cout << "Enter the y-radius of the circle: ";
    cin >> radius_y;
    cout << "Enter the center coordinate: ";
    cin >> xc >> yc;
}
                                                                                                  
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    glPointSize(2.0);
    int x = 0, y = radius_y;
    int p = (radius_y * radius_y) + (1/4.0 * radius_x * radius_x) - (radius_x * radius_x * radius_y);
    int dy = 0;
    int dx = 1;
    
    glBegin(GL_POINTS);
    
    //Plotting the 1st octant
    while(dy < dx)
    {
    	glVertex2i(x + xc, y + yc);
    	glVertex2i(x + xc, -y + yc);
    	glVertex2i(-x + xc, -y + yc);
    	glVertex2i(-x + xc, y + yc);
    	x += 1;
    	
    	
    	if(p < 0)
    	{
    		dy = 2 * (radius_y * radius_y) * x;
    		dx = 2 * (radius_x * radius_x) * y;
    		p += dy + (radius_y * radius_y);
    		
    	}
    	else
    	{
    		y -= 1;
    		dy = 2 * (radius_y * radius_y) * x;
    		dx = 2 * (radius_x * radius_x) * y;
    		p += dy + (radius_y * radius_y) - dx;
    	}
    	
    }
    
    //Plotting the 2nd octant
    double p1 = pow(radius_y, 2) * pow((x + 0.5), 2) + pow(radius_x, 2) * pow((y - 1), 2) - pow(radius_x, 2) * pow(radius_y, 2);
    while (y >= 0)
    {
    	glVertex2i(x + xc, y + yc);
    	glVertex2i(x + xc, -y + yc);
    	glVertex2i(-x + xc, -y + yc);
    	glVertex2i(-x + xc, y + yc);
    	y -= 1;
    	
    	if(p1 > 0)
    	{
    		dy = 2 * (radius_y * radius_y) * x;
    		dx = 2 * (radius_x * radius_x) * y;
    		p1 += pow(radius_x, 2) - dx;
    	}
    	else
    	{
    		x += 1;
    		dy = 2 * (radius_y * radius_y) * x;
    		dx = 2 * (radius_x * radius_x) * y;
    		p1 += pow(radius_x, 2) - dx + dy;
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
    glutCreateWindow("Ellipse");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
