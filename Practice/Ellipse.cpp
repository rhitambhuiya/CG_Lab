#include <GL/glut.h>
#include <bits/stdc++.h>

using namespace std;

float b_col[3] = {1.0, 0, 0};
float f_col[3] = {0, 1.0, 1.0};
float o_col[3] = {1.0, 0.0 ,0.0};

bool isSameCol(float c1[3], float c2[3])
{
    return (c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2]);
}

void init()
{
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void floodFill(int x, int y)
{
    float c_col[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, c_col);

    if (isSameCol(c_col, o_col))
    {
        glPointSize(2.0);
        glColor3fv(f_col);

        glBegin(GL_POINTS);
        glVertex2i(x, y);

        glEnd();
        glFlush();

        floodFill(x - 2, y);
        floodFill(x, y - 2);
        floodFill(x + 2, y);
        floodFill(x, y + 2);
    }
}

void boundaryFill(int x, int y)
{
    float curr_col[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, curr_col);

    if(isSameCol(curr_col, b_col) or isSameCol(curr_col, f_col))
        return;

    glPointSize(2.0);
    glColor3fv(f_col);

    glBegin(GL_POINTS);
    glVertex2i(x, y);

    glEnd();
    glFlush();

    boundaryFill(x - 2, y);
    boundaryFill(x, y - 2);
    boundaryFill(x + 2, y);
    boundaryFill(x, y + 2);
}

void drawEllipse(int cx, int cy, int rx, int ry)
{
    int n = 360;
    for(int i = 0; i < n; i++)
    {
        float angle = (2 * i * 3.141592) / n;
        float x = cx + rx * cos(angle);
        float y = cy + ry * sin(angle);
        glVertex2f(x, y);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(5.0);
    glColor3fv(b_col);
    //For Flood Fill
    // glBegin(GL_POLYGON);
    // drawEllipse(200, 200, 100, 75);
    // glEnd();
    // glFlush();
    //floodFill(200, 200);
    //glFlush();
    
    //For Boundary Fill
    glColor3fv(b_col);
    glBegin(GL_LINE_LOOP);
    drawEllipse(350, 350, 100, 75);
    glEnd();
    //boundaryFill(350, 350);
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON and state == GLUT_DOWN)
    {
        boundaryFill(x, 500 - y);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Ellipse");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}