#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>

#define BUFFER_SIZE 100


void plotDivisionLines()    {
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
}


void renderSpacedBitmapString(float x, float y, void *font, char *string) {
    char *c;
    int x1 = x;
    for (c = string; *c != '\0'; c++) {
        glRasterPos2f(x1, y);
        glutBitmapCharacter(font, *c);
        x1 = x1 + glutBitmapWidth(font, *c);
    }
}


void markString(char *string, int x, int y, int x_offset, int y_offset) {
    glColor3f(255.0, 0, 0.0); // red color
    renderSpacedBitmapString(x+x_offset, y+y_offset, GLUT_BITMAP_HELVETICA_10, string);
    glFlush();
}


void plotPoint(int x, int y)    {
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}


void plotLineBresenham(int x1, int x2, int y1, int y2) {
    
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x,y;

    dx = x2-x1;
    dy = y2-y1;

    if (dx < 0) dx = -dx;
    if (dy < 0) dy = -dy;
    
    incx = 1;
    if (x2 < x1) incx = -1;
    
    incy = 1;
    if (y2 < y1) incy = -1;
    
    x = x1; y = y1;
    if (dx > dy) {
        plotPoint(x, y);
        e = 2 * dy-dx;
        inc1 = 2*(dy-dx);
        inc2 = 2*dy;
        for (i=0; i<dx; i++) {
            if (e >= 0) {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            plotPoint(x, y);
        }

    } else {
        plotPoint(x, y);
        e = 2 * dx-dy;
        inc1 = 2*(dx-dy);
        inc2 = 2*dx;
        for (i=0; i<dy; i++) {
            if (e >= 0) {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            plotPoint(x, y);
        }
    }
}


void display()  {
    glClear(GL_COLOR_BUFFER_BIT);
    plotDivisionLines();
    
    int start_x, start_y, end_x, end_y;
    printf("\nEnter Start Coordinates (x y): ");
    scanf(" %d %d", &start_x, &start_y);
    printf("Enter End Coordinates (x y): ");
    scanf(" %d %d", &end_x, &end_y);
    
    // plotLineDDA(10, -20, 100, -80);
    plotLineBresenham(start_x, start_y, end_x, end_y);
    plotLineBresenham(start_x, -start_y, end_x, -end_y);
    plotLineBresenham(-start_x, start_y, -end_x, end_y);
    plotLineBresenham(-start_x, -start_y, -end_x, -end_y);

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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Ex3 - Bresenham Line Drawing");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 1;
}
