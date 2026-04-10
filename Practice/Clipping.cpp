#include <GL/glut.h>
#include <cmath>

int left = 1;
int right = 2;
int bottom = 4;
int up = 8;

int x1 = 150, Y1 = 350;
int x2 = 450, y2 = 50;

int xmin = 200, xmax = 400;
int ymin = 100, ymax = 300;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0); //sets background color
	glMatrixMode(GL_PROJECTION); //sets the projection matrix
	gluOrtho2D(0,500,0,500); //defines the 2d orthographic projection
}

void drawWindow(){
    glColor3f(0,0,0);
    glLineWidth(4);

    glBegin(GL_LINE_LOOP);
        glVertex2i(xmin,ymin);
        glVertex2i(xmax,ymin);
        glVertex2i(xmax,ymax);
        glVertex2i(xmin,ymax);
    glEnd();
    glFlush();

}

void drawLine(){
    glColor3f(1,0,0);
    glLineWidth(4);

    glBegin(GL_LINES);
        glVertex2i(x1,Y1);
        glVertex2i(x2,y2);
    glEnd();
    glFlush();

}

int getCode(float x, float y){
    int code =0;
    if(x < xmin) code |= left;
    else if(x > xmax) code |= right;

    if(y < ymin) code |= bottom;
    else if(y > ymax) code |= up;

    return code;
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT); //clears the screen
    drawWindow();
    drawLine();

    float x,y;
    //line wq y = mx+c
    float m = (y2-Y1)/(x2-x1);
    float c = Y1 - (x1*m);

    bool accept = false;

    while(true){
        int code1 = getCode(x1,Y1);
        int code2 = getCode(x2,y2);

        if(code1 == 0 && code2 == 0){
            accept = true;
            break;
        }
        else if(code1 & code2 ) break;

        else{
            int codeOut = code1 ? code1 : code2;

            if(codeOut & left){
                x = xmin;
                y = m*x + c;
            }
            else if(codeOut & right){
                x = xmax;
                y = m*x + c;
            }
            else if(codeOut & up){
                y = ymax;
                x = (y-c)/m;
            }
            else if(codeOut & bottom){
                y = ymin;
                x = (y-c)/m;
            }

            if(codeOut == code1){
                x1 = x;
                Y1 = y;
            }
            else{
                x2 = x;
                y2 = y;
            }
        }
    }

    if(accept){
        glColor3f(1,1,0);
        glLineWidth(4);

    glBegin(GL_LINES);
        glVertex2i(x1,Y1);
        glVertex2i(x2,y2);
    glEnd();
    glFlush();
    }

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv); //initialises glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Window Name");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}