#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);
}

void rotatePoint(float x, float y, float angle)
{
    angle *= 3.141592 / 180.0;

    float x_new = x * cos(angle) - y * sin(angle);
    float y_new = x * sin(angle) + y * cos(angle);

    glVertex2f(x_new, y_new);
}

void reflectX(float x, float y)
{
    glVertex2f(x, -y);
}

void scale(float x, float y, int scale_factor)
{
    glVertex2f(x * scale_factor, y * scale_factor);
}

void DDA(float X1, float Y1, float X2, float Y2)
{
    float x = X1;  
    float y = Y1;

    float dx = X2 - X1;
    float dy = Y2 - Y1;
    if (dx == 0) //vertical line
    {
        y = min(Y1, Y2);
        Y2 = max(Y1, Y2);
        while(y <= Y2)
        {   
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_POINTS);
            glVertex2f(x, y);
            glEnd();
            
            glColor3f(0.0, 0.0, 1.0);
            glBegin(GL_POINTS);
            rotatePoint(x, y, 90);
            scale(x, y, 2);
            reflectX(x, y);
            glEnd();

            y += 1;
        }
    }
    else
    {
        float m = dy / dx;
        int factor = 1;
        if(m < 0)
            factor = -1;

        m = fabs(m);

        if (m <= 1)
        {
            while (x <= X2)
            {
                glColor3f(1.0, 0.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
                
                glColor3f(0.0, 0.0, 1.0);
                glBegin(GL_POINTS);
                rotatePoint(x, y, 90);
                scale(x, y, 2);
                reflectX(x, y);
                glEnd();
                x += 1;
                y += m * factor;
            }
        }
        else
        {
            while (x <= X2)
            {
                glColor3f(1.0, 0.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2f(x, y);
                glEnd();
                
                glColor3f(0.0, 0.0, 1.0);
                glBegin(GL_POINTS);
                rotatePoint(x, y, 90);
                scale(x, y, 2);
                reflectX(x, y);
                glEnd();
                y += factor;
                x += (1.0 / m);
            }
        }
    }
}

void drawRoof()
{
    DDA(100, 100, 150, 175);
    DDA(150, 175, 200, 100);
    DDA(100, 100, 200, 100);
}

void drawWalls()
{
    DDA(100, 100, 100, 0);
    DDA(100, 0, 200, 0);
    DDA(200, 0, 200, 100);
    DDA(100, 100, 200, 100);
}

void drawDoor()
{
    DDA(130, 0, 170, 0);
    DDA(170, 0, 170, 50);
    DDA(130, 50, 170, 50);
    DDA(130, 0, 130, 50);
}

void drawWindow()
{
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    drawRoof();
    drawWalls();
    drawDoor();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("House");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}