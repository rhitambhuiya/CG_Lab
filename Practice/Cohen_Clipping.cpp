#include <iostream>
#include <GL/glut.h>

int top = 8;
int down = 4;
int right = 2;
int left = 1;

int X1 = 50, Y1 = 50;
int X2 = 350, Y2 = 350;

int xmin = 100, xmax = 300;
int ymin = 100, ymax = 300;

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

void clip()
{
    float m = (Y2 - Y1) * 1.0 / (X2 - X1);
    float c = Y1 - (m * X1);
    float x, y;
    bool accept = false;

    while(true)
    {
        int code1 = getCode(X1, Y1);
        int code2 = getCode(X2, Y2);

        if(code1 == 0 and code2 == 0)
        {
            accept = true;
            break;
        }

        else if(code1 & code2)
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
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINE_STRIP);
        glVertex2i(X1, Y1);
        glVertex2i(X2, Y2);
        glEnd();
    }
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void drawWindow()
{
    glLineWidth(3.0);
    glColor3f(1, 0, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
}

void drawLine()
{
    glLineWidth(3.0);
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex2i(X1, Y1);
    glVertex2i(X2, Y2);
    glEnd(); 
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawWindow();
    drawLine();
    clip();

    glFlush();

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Clipping");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}