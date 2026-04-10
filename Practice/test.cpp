#include <GL/GLUT.h>
#include <bits/stdc++.h>
#define PI 3.141592

using namespace std;

float boundaryCol[3] = {1.0, 0.0, 0.0};
float fillCol[3] = {1.0, 1.0, 0.0};
int clickX = -1, clickY = -1;

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

void drawWindow()
{
    glLineWidth(5.0);
    glColor3fv(boundaryCol);
    glBegin(GL_LINE_LOOP);
    glVertex2i(100, 100);
    glVertex2i(100, 300);
    glVertex2i(300, 300);
    glVertex2i(300, 100);
    glEnd();
    glFlush();
}

void draw_Ellipse_Easy(int xc, int yc, int radius_x, int radius_y)
{
    glLineWidth(5.0);
    glColor3fv(boundaryCol);
    glBegin(GL_LINE_LOOP);
    int n = 1000; // give any large number+
    for(int i = 0; i <= n; i++)
    {
        float angle = (2.0 * PI * i) / n;
        float x = xc + radius_x * cos(angle);
        float y = yc + radius_y * sin(angle); // for circle, put radius_y = radius_x
        glVertex2f(x, y);
    }
    glEnd();
    glFlush();
}

void boundaryFill(int x, int y)
{
    float currCol[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currCol);

    if(!isSameCol(currCol, boundaryCol) && !isSameCol(currCol, fillCol))
    {
        glBegin(GL_POINTS);
        glColor3fv(fillCol);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill(x - 2, y);
        boundaryFill(x + 2, y);
        boundaryFill(x, y + 2);
        boundaryFill(x, y - 2);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);  
    draw_Ellipse_Easy(250, 250, 150, 125);
    draw_Ellipse_Easy(300, 300, 25, 25);
    draw_Ellipse_Easy(200, 300, 25, 25);
    glPointSize(2.0);
    boundaryFill(250, 250);
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        clickX = x;
        clickY = 500 - y;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Boundary Fill");
    init();
    glutDisplayFunc(display);
    //glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}