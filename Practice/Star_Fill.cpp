#include <GL/freeglut.h>
#include <cmath>
#define PI 3.14

int star[10][2]; 

float fillCol[3] = {0.0, 0.0, 1.0}; 
float oldCol[3] = {1.0, 1.0, 1.0}; 

bool isSameColor(float c1[3], float c2[3]) {
    return (std::abs(c1[0] - c2[0]) < 0.01f && 
            std::abs(c1[1] - c2[1]) < 0.01f && 
            std::abs(c1[2] - c2[2]) < 0.01f);
}

void floodFill8(int x, int y) {
    float currentColor[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

    
    if (isSameColor(currentColor, oldCol)) {
        
        glBegin(GL_POINTS);
            glColor3fv(fillCol);
            glVertex2i(x, y);
        glEnd();
        glFlush(); 

        floodFill8(x + 2, y);
        floodFill8(x - 2, y);
        floodFill8(x, y + 2);
        floodFill8(x, y - 2);
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);

    int points = 5;
    int R = 150, r = 70;
    int cx = 250, cy = 250;

    for(int i = 0; i < points * 2; i++)
    {
        float angle = (i * PI) / points;
        int radius = (i % 2 == 0) ? R : r;

        int x = cx + radius * cos(angle);
        int y = cy + radius * sin(angle);

        star[i][0] = x;
        star[i][1] = y;
    }
}

void display()
{
    glLoadIdentity();
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 10; i++) {
        glVertex2iv(star[i]); 
    }

    glEnd();
    glPointSize(2.0);
    floodFill8(250, 250);
    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Star");
    init(); 
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}