#include<GL/glut.h>


// POINTS, LINES, LINE_STRIP, LINE_LOOP, TRIANGLES, TRIANGLE STRIP,
// TRIANGLE FAN, QUADS, QUAD_STRIP, POLYGON

void plotPoints()   {
    glBegin(GL_POINTS);
    glVertex2d(150,100);
    glVertex2d(100,230);
    glVertex2d(170,130);
    glVertex2d(300,350);
    glEnd();
}


void plotLines()    {
    glBegin(GL_LINES);
    glVertex2d(150,100);
    glVertex2d(100,230);
    glVertex2d(170,130);
    glVertex2d(300,350);
    glEnd();
}


void plotLineStrip()    {
    glBegin(GL_LINE_STRIP);
    glVertex2d(150,100);
    glVertex2d(100,230);
    glVertex2d(170,130);
    glVertex2d(300,350);
    glEnd();
}


void plotLineLoop() {
    glBegin(GL_LINE_LOOP);
    glVertex2d(150,100);
    glVertex2d(100,230);
    glVertex2d(170,130);
    glVertex2d(300,350);
    glEnd();
}


void plotTriangles()    {
    glBegin(GL_TRIANGLES);
    glVertex2d(150,100);
    glVertex2d(100,230);
    glVertex2d(170,130);
    glEnd();
}


void plotTriangleStrip()    {
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2d(150,100);
    glVertex2d(100,230);
    glVertex2d(170,130);
    glVertex2d(300,100);
    glEnd();
}


void plotTriangleFan()  {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2d(500, 50);
    glVertex2d(400, 100);
    glVertex2d(450, 200);
    glVertex2d(600, 180);
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
    glVertex2d(450, 250);
    glVertex2d(600, 300);
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
    // plotLines();
    // plotLineStrip();
    // plotLineLoop();
    // plotTriangles();
    // plotTriangleStrip();
    // plotTriangleFan();
    plotQuads();
    plotQuadStrip();
    plotPolygon();
    glFlush();
}


void init()   {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f,0.0f,0.0f);
    glPointSize(10);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);
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