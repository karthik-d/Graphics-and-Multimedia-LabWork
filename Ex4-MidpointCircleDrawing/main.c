#include <GL/glut.h>
#include <stdio.h>


void plotPoint(int x, int y, int x_offset, int y_offset)    {
    glBegin(GL_POINTS);
    glVertex2d(x + x_offset, y + y_offset);
    glEnd();
}


void plotCircle(int center_x, int center_y, int radius) {
    int x_k = 0;
    int y_k = radius;
    int p_k = 1 - radius;
    
    plotPoint(x_k, y_k, center_x, center_y);
    while(x_k <= y_k)   {
        if(p_k < 0) {
            plotPoint(x_k + 1, y_k, center_x, center_y);
            x_k += 1;
            p_k += (2*x_k) + 1;
        }
        else{
            plotPoint(x_k + 1, y_k - 1, center_x, center_y);
            x_k += 1;
            y_k += -1;
            p_k += (2*x_k) - (2*y_k) + 1;
        }
        printf("\n(%d, %d)", x_k, y_k);
    }
}


void display_figure()   {
    ;
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
    // glutCreateWindow("Ex4b - Figure with Circles");
    // glutDisplayFunc(display_figure);

    init();
    glutMainLoop();    
    return 1;
}