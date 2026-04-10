#include <GL/glut.h>
#include <iostream>
#include <cmath>
#define PI 3.141592

using namespace std;

int radius_x, radius_y;
int xc, yc;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void input()
{
    cout << "Enter the x-radius of the ellipse: ";
    cin >> radius_x;
    cout << "Enter the y-radius of the ellipse: ";
    cin >> radius_y;
    cout << "Enter the center coordinate: ";
    cin >> xc >> yc;
}

void draw_Ellipse_Easy(int xc, int yc, int radius_x, int radius_y)
{
    int n = 1000; // give any large number
    for(int i = 0; i <= n; i++)
    {
        float angle = (2.0 * PI * i) / n;
        float x = xc + radius_x * cos(angle);
        float y = yc + radius_y * sin(angle); // for circle, put radius_y = radius_x
        glVertex2f(x, y);
    }
}

void draw_Ellipse_Algorithm(int xc, int yc, int rx, int ry)
{
    int x = 0, y = ry;
    int p = (ry * ry) + (rx * rx * 0.25) - (rx * rx * ry);
    int dy = 0, dx = 1;
    while(dy < dx)
    {
        glVertex2i(x + xc, y + yc);
        glVertex2i(-x + xc, y + yc);
        glVertex2i(-x + xc, -y + yc);
        glVertex2i(x + xc, -y + yc);
        
        x += 1;
        if(p < 0){
            dy = ry * ry * x;
            dx = rx * rx * y;
            p += 2 * dy + ry * ry;
        }
        else
        {
            y -= 1;
            dy = ry * ry * x;
            dx = rx * rx * y;
            p += 2 * dy + (ry * ry) - 2 * dx;
        }
    }

    double p1 = ry * ry * pow(x + 0.5, 2) + rx * rx * pow(y - 1, 2.0) - rx * rx * ry * ry;
    while(y >= 0)
    {
        glVertex2i(x + xc, y + yc);
        glVertex2i(-x + xc, y + yc);
        glVertex2i(-x + xc, -y + yc);
        glVertex2i(x + xc, -y + yc);

        y -= 1;
        dx = rx * rx * y;
        dy = ry * ry * x;
        if(p1 > 0)
            p1 += rx * rx - 2 * dx;
        else
        {
            x += 1;
            dy = ry * ry * x;
            p1 += rx * rx + 2 * dy - 2 * dx;
        }
    }
}
                                                                                                  
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);

    glPointSize(2.0);
    glBegin(GL_POINTS);
    draw_Ellipse_Algorithm(xc, yc, radius_x, radius_y);
    glEnd();

    // glLineWidth(2.0);
    // glBegin(GL_LINE_STRIP);
    // draw_Ellipse_Easy(xc, yc, radius_x, radius_y);
    // glEnd();
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