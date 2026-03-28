#include <GL/glut.h>
#include <stdio.h>

// Window size
int winWidth = 500, winHeight = 500;

// Clipping window
float xmin, ymin, xmax, ymax;

// Line coordinates
float x_start, y_start, x_end, y_end;

// Region codes
#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

// Compute region code
int computeCode(float x, float y) {
    int code = INSIDE;

    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;

    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;

    return code;
}

// Cohen–Sutherland Clipping
void cohenSutherlandClip() {
    float x, y;

    int code1 = computeCode(x_start, y_start);
    int code2 = computeCode(x_end, y_end);

    int accept = 0;

    while (1) {
        if (code1 == 0 && code2 == 0) {
            accept = 1;
            break;
        }
        else if (code1 & code2) {
            break;
        }
        else {
            int code_out = code1 ? code1 : code2;

            if (code_out & TOP) {
                x = x_start + (x_end - x_start) * (ymax - y_start) / (y_end - y_start);
                y = ymax;
            }
            else if (code_out & BOTTOM) {
                x = x_start + (x_end - x_start) * (ymin - y_start) / (y_end - y_start);
                y = ymin;
            }
            else if (code_out & RIGHT) {
                y = y_start + (y_end - y_start) * (xmax - x_start) / (x_end - x_start);
                x = xmax;
            }
            else if (code_out & LEFT) {
                y = y_start + (y_end - y_start) * (xmin - x_start) / (x_end - x_start);
                x = xmin;
            }

            if (code_out == code1) {
                x_start = x;
                y_start = y;
                code1 = computeCode(x_start, y_start);
            } else {
                x_end = x;
                y_end = y;
                code2 = computeCode(x_end, y_end);
            }
        }
    }

    // Draw clipped line
    if (accept) {
        glColor3f(0, 1, 0); // Green
        glBegin(GL_LINES);
        glVertex2f(x_start, y_start);
        glVertex2f(x_end, y_end);
        glEnd();
    }
}

// Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window (white)
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Original line (red)
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x_start, y_start);
    glVertex2f(x_end, y_end);
    glEnd();

    // Clipped line
    cohenSutherlandClip();

    glFlush();
}

// Initialization
void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, winWidth, 0, winHeight);
}

// Main
int main(int argc, char** argv) {

    float width, height;

    // Input clipping window size
    printf("Enter clipping window width and height: ");
    scanf("%f %f", &width, &height);

    // Center the clipping window
    xmin = (winWidth - width) / 2;
    xmax = xmin + width;
    ymin = (winHeight - height) / 2;
    ymax = ymin + height;

    // Input line endpoints
    printf("Enter line endpoints (x_start y_start x_end y_end): ");
    scanf("%f %f %f %f", &x_start, &y_start, &x_end, &y_end);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Cohen-Sutherland Line Clipping (Centered)");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
