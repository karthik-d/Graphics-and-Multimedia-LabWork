#include <GL/glut.h>


void plotDivisionLines()    {
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
}


void plotLineDDA(start_x, start_y, end_x, end_y)  {
    
    float slope = (end_y - end_x) / (start_x - start_y);
    float abs_slope = slope;
    short l_to_r;
    
    if(slope>0) {
        abs_slope = slope;
    }
    else    {
        abs_slope = -1 * slope;
    }
}


void display()  {
    glClear(GL_COLOR_BUFFER_BIT);
    plotDivisionLines();
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


int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Ex2 - DDA Line Drawing");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 1;
}