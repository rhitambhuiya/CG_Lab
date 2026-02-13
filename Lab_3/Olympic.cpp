#include <GL/glut.h>
#include <cmath>

// Draw a single ring with given position, radius, and color
void drawRing(float x, float y, float radius, float r, float g, float b) {
    int num_segments = 100;
    
    glColor3f(r, g, b);
    glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    float R = 0.7f;   // ring radius
    float dx = 1.4f;  // horizontal spacing
    float dy = 0.6f;  // vertical spacing

    // Draw bottom rings first (so they appear under top rings)
    drawRing(-0.7f, -dy, R, 1.0f, 0.8f, 0.0f);  // Yellow
    drawRing(0.7f, -dy, R, 0.0f, 0.6f, 0.2f);   // Green

    // Draw top rings
    drawRing(-1.4f, 0.0f, R, 0.0f, 0.5f, 0.8f);  // Blue
    drawRing(0.0f, 0.0f, R, 0.0f, 0.0f, 0.0f);   // Black
    drawRing(1.4f, 0.0f, R, 0.9f, 0.0f, 0.1f);   // Red

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    gluOrtho2D(-4.0f * aspect, 4.0f * aspect, -3.0f, 3.0f);

    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Olympic Rings - OpenGL");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

