#include <GL/glut.h>

void drawH(float x, float y)
{
    glBegin(GL_LINES);
        glVertex2f(x, y);     glVertex2f(x, y + 0.2);
        glVertex2f(x + 0.1, y); glVertex2f(x + 0.1, y + 0.2);
        glVertex2f(x, y + 0.1); glVertex2f(x + 0.1, y + 0.1);
    glEnd();
}

void drawE(float x, float y)
{
    glBegin(GL_LINES);
        glVertex2f(x, y);     glVertex2f(x, y + 0.2);
        glVertex2f(x, y + 0.2); glVertex2f(x + 0.1, y + 0.2);
        glVertex2f(x, y + 0.1); glVertex2f(x + 0.08, y + 0.1);
        glVertex2f(x, y);     glVertex2f(x + 0.1, y);
    glEnd();
}

void drawL(float x, float y)
{
    glBegin(GL_LINES);
        glVertex2f(x, y);     glVertex2f(x, y + 0.2);
        glVertex2f(x, y);     glVertex2f(x + 0.1, y);
    glEnd();
}

void drawO(float x, float y)
{
    glBegin(GL_LINES);
        glVertex2f(x, y);         glVertex2f(x, y + 0.2);
        glVertex2f(x, y + 0.2);   glVertex2f(x + 0.1, y + 0.2);
        glVertex2f(x + 0.1, y + 0.2); glVertex2f(x + 0.1, y);
        glVertex2f(x + 0.1, y);   glVertex2f(x, y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);

    float startX = -0.9f;
    float startY = 0.0f;
    float gap = 0.15f;

    drawH(startX, startY);
    drawE(startX + gap, startY);
    drawL(startX + 2 * gap, startY);
    drawL(startX + 3 * gap, startY);
    drawO(startX + 4 * gap, startY);

    glFlush();
}

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("HELLO using Lines");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

