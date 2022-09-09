#include <GL/glut.h>
#include <stdio.h>


void plotPoint(int x, int y)    {
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}


void plotCircle(int center_x, int center_y, int radius) {
    x_k = 0;
    y_k = radius;
    p_k = 1 - radius;
    
    while(x_k >= y_k)   {
        if(p_k < 0) {

        }
    }
}


void display_circle()   {
    glClear(GL_COLOR_BUFFER_BIT);
    plotCircle(0, 0, 80);
    plotCircle(160, 120, 40);
    glFlush();
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}


int main(int argc, char **argv)  {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);

    // circle
    glutCreateWindow("Ex4a - Midpoint Circle");
    glutDisplayFunc(display_circle);
    
    // figure
    glutCreateWindow("Ex4b - Figure with Circles");
    glutDisplayFunc(display_figure);

    init();
    glutMainLoop();    
    return 1;
}