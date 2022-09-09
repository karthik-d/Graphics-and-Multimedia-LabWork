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


void markString(char *string, int x, int y, int x_offset, int y_offset, short large) {
    void *size = (large ? GLUT_BITMAP_HELVETICA_12 : GLUT_BITMAP_HELVETICA_10);
    glColor3f(255.0, 0, 0.0); // red color
    printf("\n%s", string);
    renderSpacedBitmapString(x+x_offset, y+y_offset, size, string);
    glFlush();
}


// POINTS, LINES, LINE_STRIP, LINE_LOOP, TRIANGLES, TRIANGLE STRIP,
// TRIANGLE FAN, QUADS, QUAD_STRIP, POLYGON

void plotPoints()   {
    glBegin(GL_POINTS);
    // line    
    glVertex2d(20, 30);
    glVertex2d(130, 40);
    glVertex2d(170, 50);
    glVertex2d(120, 140);
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


void plotLabels()   {
    
    markString("POINTS and LINES", 10, 150, 0, 0, 1);
    markString("A(20, 30)", 20, 30, -5, 5, 0);
    markString("B(130, 40)", 130, 40, -5, 5, 0);
    markString("C(170, 50)", 170, 50, -5, 5, 0);
    markString("D(120, 140)", 120, 140, -5, 5, 0);

    markString("LINE STRIP", 30, 310, 0, 0, 1);
    markString("E(20, 190)", 20, 190, -5, 5, 0);
    markString("F(130, 200)", 130, 200, -5, 5, 0);
    markString("G(50, 230)", 50, 230, -5, 5, 0);
    markString("H(120, 300)", 120, 300, -5, 5, 0);

    markString("LINE LOOP", 30, 460, 0, 0, 1);
    markString("A(20, 350)", 20, 350, -5, 5, 0);
    markString("B(130, 360)", 130, 360, -5, 5, 0);
    markString("C(170, 390)", 170, 390, -5, 5, 0);
    markString("D(120, 460)", 120, 460, -5, 5, 0);

    markString("TRAINGLES", 300, 460, 0, 0, 1);
    markString("A(230, 350)", 230, 350, 5, -10, 0);
    markString("B(230, 450)", 230, 450, 5, 5, 0);
    markString("C(370, 400)", 370, 400, -20, 10, 0);

    markString("TRAINGLE STRIP", 240, 310, 0, 0, 1);
    markString("A(230, 190)", 230, 190, 5, -10, 0);
    markString("B(230, 240)", 230, 240, -20, 15, 0);
    markString("C(380, 210)", 380, 210, -10, 10, 0);
    markString("D(300, 280)", 300, 280, -20, 10, 0);

    markString("TRAINGLE FAN", 240, 150, 0, 0, 1);
    markString("A(230, 30)", 230, 30, 5, -10, 0);
    markString("B(230, 120)", 230, 120, -20, 15, 0);
    markString("C(380, 150)", 380, 150, -10, 10, 0);
    markString("D(300, 30)", 300, 30, 10, 10, 0);

    markString("QUADS", 500, 460, 0, 0, 1);
    markString("A(500, 450)", 500, 450, 20, -5, 0);
    markString("B(400, 400)", 400, 400, -40, -30, 0);
    markString("C(450, 350)", 450, 350, 25, 0, 0);
    markString("D(600, 400)", 600, 400, -20, 10, 0);

    markString("QUAD STRIP", 500, 460, 0, 0, 1);
    markString("A(500, 320)", 500, 320, 20, -5, 0);
    markString("B(400, 290)", 400, 290, -40, -30, 0);
    markString("D(450, 190)", 450, 190, -20, 10, 0);
    markString("C(480, 270)", 480, 270, 25, 0, 0);
    markString("D(620, 350)", 620, 350, -20, 10, 0);

    (480, 160);
    glVertex2d(560, 160);
    glVertex2d(600, 70);
    glVertex2d(560, 40);
    glVertex2d(480, 40);
    glVertex2d(410, 90);
    markString("POLYGONS", 500, 180, 0, 0, 1);
    markString("A(480, 160)", 480, 160, 10, 5, 0);
    markString("B(560, 160)", 560, 160, 20, -5, 0);
    markString("C(600, 70)", 600, 70, -15, -20, 0);
    markString("D(560, 40)", 560, 40, -5, -20, 0);
    markString("E(480, 40)", 480, 40, 0, -20, 0);
    markString("F(410, 90)", 410, 90, -25, -30, 0);
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
    glVertex2d(480, 270);
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
    plotLabels();
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
    glutCreateWindow("Ex1A - OpenGL Primitives");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 1;
}