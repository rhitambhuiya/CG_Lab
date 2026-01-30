#include <GL/glut.h>
#include <iostream>
#include <vector>

using namespace std;

int n;
vector<pair<int, int>> points;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);

    glBegin(GL_LINES);

    for (int i = 0; i < n; i++)
    {
        // line from point i to next point
        glVertex2i(points[i].first, points[i].second);
        glVertex2i(points[i + 1].first, points[i + 1].second);
    }

    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    cout << "Enter the number of points: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter point " << i + 1 << ": ";
        int a, b;
        cin >> a >> b;
        points.push_back({a, b});
    }

    // close the shape
    points.push_back(points[0]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Draw Lines (GL_LINES)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

