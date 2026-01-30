#include <GL/glut.h>
#include <vector>
using namespace std;

vector<pair<int,int>> points;
int winWidth = 500, winHeight = 500;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, winWidth, 0, winHeight);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5);

    glBegin(GL_POINTS);
    for (auto &p : points)
        glVertex2i(p.first, p.second);
    glEnd();

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert y coordinate (GLUT uses top-left origin)
        int yOpenGL = winHeight - y;

        points.push_back({x, yOpenGL});
        glutPostRedisplay();  // redraw with new point
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Click to Place Points");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}

