#include <GL/glut.h>
#include <stdio.h>

#define BUFFER_SIZE 200


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
    printf("\n%s", string);
    renderSpacedBitmapString(x+x_offset, y+y_offset, GLUT_BITMAP_HELVETICA_12, string);
    glFlush();
}


// POINTS, LINES, LINE_STRIP, LINE_LOOP, TRIANGLES, TRIANGLE STRIP,
// TRIANGLE FAN, QUADS, QUAD_STRIP, POLYGON

void plotPoints()   {
    char *point_label = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    glBegin(GL_POINTS);
    // line
    sprintf(point_label, "(%d, %d)", 20, 30);
    glVertex2d(20, 30);
    markString(point_label, 20, 30, 0, 0);
    glVertex2d(130, 40);
    markString("(130, 40)", 130, 40, 5, 5);
    glVertex2d(170, 50);
    markString("(170, 50)", 170, 50, 5, 5);
    glVertex2d(120, 140);
    markString("(120, 140)", 120, 140, 5, 5);
    // line strip
    glVertex2d(20, 190);
    glVertex2d(130, 200);
    glVertex2d(50, 230);
    glVertex2d(120, 300);
    // line loop
    glVertex2d(20, 350);
    glVertex2d(130, 360);
    glVertex2d(170, 390);
    glVertex2d(120, 460);
    // triangle
    glVertex2d(230, 350);
    glVertex2d(230, 450);
    glVertex2d(370, 400);
    // triangle strip
    glVertex2d(230, 190);
    glVertex2d(230, 240);
    glVertex2d(380, 210);
    glVertex2d(300, 280);
    // triangle fan
    glVertex2d(230, 30);
    glVertex2d(230, 120);
    glVertex2d(380, 150);
    glVertex2d(300, 30);
    // quads
    glVertex2d(500, 450);
    glVertex2d(400, 400);
    glVertex2d(450, 350);
    glVertex2d(600, 400);
    // quad strip
    glVertex2d(500, 320);
    glVertex2d(400, 290);
    glVertex2d(450, 190);
    glVertex2d(600, 240);
    glVertex2d(620, 350);
    // polygon
    glVertex2d(480, 160);
    glVertex2d(560, 160);
    glVertex2d(600, 70);
    glVertex2d(560, 40);
    glVertex2d(480, 40);
    glVertex2d(410, 90);
    glEnd();
}


void plotLines()    {
    glBegin(GL_LINES);
    glVertex2d(20, 30);
    glVertex2d(130, 40);
    glVertex2d(170, 50);
    glVertex2d(120, 140);
    glEnd();
}


void plotLineStrip()    {
    glBegin(GL_LINE_STRIP);
    glVertex2d(20, 190);
    glVertex2d(130, 200);
    glVertex2d(50, 230);
    glVertex2d(120, 300);
    glEnd();
}


void plotLineLoop() {
    glBegin(GL_LINE_LOOP);
    glVertex2d(20, 350);
    glVertex2d(130, 360);
    glVertex2d(170, 390);
    glVertex2d(120, 460);
    glEnd();
}


void plotTriangles()    {
    glBegin(GL_TRIANGLES);
    glVertex2d(230, 350);
    glVertex2d(230, 450);
    glVertex2d(370, 400);
    glEnd();
}


void plotTriangleStrip()    {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(230, 190);
    glVertex2d(230, 240);
    glVertex2d(380, 210);
    glVertex2d(300, 280);
    glEnd();
}


void plotTriangleFan()  {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(230, 30);
    glVertex2d(230, 120);
    glVertex2d(380, 150);
    glVertex2d(300, 30);
    glEnd();
}


void plotQuads()    {
    glBegin(GL_QUADS);
    glVertex2d(500, 450);
    glVertex2d(400, 400);
    glVertex2d(450, 350);
    glVertex2d(600, 400);
    glEnd();
}


void plotQuadStrip()    {
    glBegin(GL_QUAD_STRIP);
    glVertex2d(500, 320);
    glVertex2d(400, 290);
    glVertex2d(450, 190);
    glVertex2d(600, 240);
    glVertex2d(620, 350);
    glEnd();
}


void plotPolygon()    {
    glBegin(GL_POLYGON);
    glVertex2d(480, 160);
    glVertex2d(560, 160);
    glVertex2d(600, 70);
    glVertex2d(560, 40);
    glVertex2d(480, 40);
    glVertex2d(410, 90);
    glEnd();
}


void display()    {
    glClear(GL_COLOR_BUFFER_BIT);
    plotPoints();
    glColor3f(0.0f, 0.0f, 0.0f);
    plotLines();
    plotLineStrip();
    plotLineLoop();
    plotTriangles();
    plotTriangleStrip();
    plotTriangleFan();
    plotQuads();
    plotQuadStrip();
    plotPolygon();
    glFlush();
}


void init()   {
    glClearColor(1.0, 1.0, 1.0,0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}


int main(int argc,char* argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutCreateWindow("Ex1 - Primitives and Checkboard");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 1;
}