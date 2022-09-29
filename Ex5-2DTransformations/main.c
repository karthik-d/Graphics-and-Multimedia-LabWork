#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654


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
    renderSpacedBitmapString(x+x_offset, y+y_offset, GLUT_BITMAP_HELVETICA_12, string);
    glFlush();
}


float** multiplyMatrices(float **m1, float **m2, int r1, int c1, int c2)    {
    // assume compatible matrices
    float **res = (float**)malloc(sizeof(float*)*r1);
    for(int i=0; i<r1; i++) {
        *(res+i) = (float*)malloc(sizeof(float)*c2);
        for(int j=0; j<c2; j++) {
            res[i][j] = 0;
            for(int k=0;k<c1;k++)   {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return res;
}


void displayMatrix(float **matrix, int r, int c)  {
    printf("\n");
    for(int i=0;i<r;i++)    {
        for(int j=0; j<c; j++)  {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}


void plotDivisionLines()    {
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
}


void plotPoint(int x, int y, int x_offset, int y_offset)    {
    glBegin(GL_POINTS);
    glVertex2d(x + x_offset, y + y_offset);
    glEnd();
}


void plotTriangle(int *xs, int *ys)   {
    glBegin(GL_TRIANGLES);
    for(int i=0; i<3; i++)  {
        glVertex2d(xs[i], ys[i]);
    }
    glEnd();
}


float** makeTriangleMatrix(int *xs, int *ys)  {
    float **res = (float**)malloc(sizeof(float*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (float*)malloc(sizeof(float)*3);
    }
    for(int i=0; i<3; i++) {
        res[0][i] = xs[i];
        res[1][i] = ys[i];
        res[2][i] = 1;
    }
    return res;
}


float** makeTranslationMatrix(int tx, int ty) {
    float **res = (float**)malloc(sizeof(float*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (float*)malloc(sizeof(float)*3);
        for(int j=0; j<3; j++) {
            if(i==j){
                res[i][j] = 1;
            }
            else{
                res[i][j] = 0;
            }
        }
    }
    res[0][2] = tx;
    res[1][2] = ty;
    return res;
}


float** makeRotationMatrix(int theta) {
    float **res = (float**)malloc(sizeof(float*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (float*)malloc(sizeof(float*)*3);
        for(int j=0; j<3; j++) {
            if(i==j){
                res[i][j] = 1;
            }
            else{
                res[i][j] = 0;
            }
        }
    }
    res[0][0] = cos(theta*PI/180);
    res[1][1] = res[0][0];
    res[0][1] = -sin(theta*PI/180);
    res[1][0] = -res[0][1];
    return res;
}


float** makeScalingMatrix(int sx, int sy)   {
    float **res = (float**)malloc(sizeof(float*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (float*)malloc(sizeof(float*)*3);
        for(int j=0; j<3; j++) {
            if(i==j){
                res[i][j] = 1;
            }
            else{
                res[i][j] = 0;
            }
        }
    }
    res[0][0] = sx;
    res[1][1] = sy;
    return res;
}


float** makeReflectionMatrix(short along_x, short along_y, short along_xeqy) {
    // truth of the first two arguments overrides the last

    float **res = (float**)malloc(sizeof(float*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (float*)malloc(sizeof(float)*3);
        for(int j=0; j<3; j++) {
            if(i==j){
                res[i][j] = 1;
            }
            else{
                res[i][j] = 0;
            }
        }
    }
    short override_xeqy = 0;
    if(along_x){
        res[1][1] = -1;
        override_xeqy = 1;
    }
    if(along_y){
        res[0][0] = -1;
        override_xeqy = 1;
    }
    if(!override_xeqy && along_xeqy)    {
        float *temp = res[0];
        res[0] = res[1];
        res[1] = temp;
    }
    return res;
}


void plotTranslatedTriangle(int *xs, int *ys, int tx, int ty)    {
    glBegin(GL_TRIANGLES);
    float **tr_matrix = makeTranslationMatrix(tx, ty);
    float **triangle_matrix = makeTriangleMatrix(xs, ys);
    float **translated_triangle = multiplyMatrices(tr_matrix, triangle_matrix, 3, 3, 3);
    for(int i=0; i<3; i++)  {
        glVertex2d((int)translated_triangle[0][i], (int)translated_triangle[1][i]);
    }
    glEnd();
}


void plotRotatedTriangle(int *xs, int *ys, int xr, int yr, int theta)    {
    // (xr, yr) --> Pivot Point
    glBegin(GL_TRIANGLES);
    
    float **triangle_matrix = makeTriangleMatrix(xs, ys);
    displayMatrix(triangle_matrix, 3, 3);
    
    float **rotated_triangle = multiplyMatrices(
        makeTranslationMatrix(xr, yr),
        multiplyMatrices(
            makeRotationMatrix(theta),
            multiplyMatrices(
                makeTranslationMatrix(-xr, -yr),
                triangle_matrix,
                3, 3, 3
            ),
            3, 3, 3
        ),
        3, 3, 3);
    
    for(int i=0; i<3; i++)  {
        glVertex2d((int)rotated_triangle[0][i], (int)rotated_triangle[1][i]);
    }
    glEnd();
}


void plotScaledTriangle(int *xs, int *ys, int xf, int yf, int sx, int sy)    {
    // (xf, yf) --> Fixed Point
    glBegin(GL_TRIANGLES);
    
    float **triangle_matrix = makeTriangleMatrix(xs, ys);
    displayMatrix(triangle_matrix, 3, 3);
    
    float **rotated_triangle = multiplyMatrices(
        makeTranslationMatrix(xf, yf),
        multiplyMatrices(
            makeScalingMatrix(sx, sy),
            multiplyMatrices(
                makeTranslationMatrix(-xf, -yf),
                triangle_matrix,
                3, 3, 3
            ),
            3, 3, 3
        ),
        3, 3, 3);
    
    for(int i=0; i<3; i++)  {
        glVertex2d((int)rotated_triangle[0][i], (int)rotated_triangle[1][i]);
    }
    glEnd();
}


void plotReflectedTriangle(int *xs, int *ys)    {
    glBegin(GL_TRIANGLES);
    
    float **xref_matrix = makeReflectionMatrix(1, 0, 0);
    float **yref_matrix = makeReflectionMatrix(0, 1, 0);
    float **xyref_matrix = makeReflectionMatrix(1, 1, 0);
    float **xeqyref_matrix = makeReflectionMatrix(0, 0, 1);
    
    float **triangle_matrix = makeTriangleMatrix(xs, ys);
    
    float **xref_triangle = multiplyMatrices(xref_matrix, triangle_matrix, 3, 3, 3);
    float **yref_triangle = multiplyMatrices(yref_matrix, triangle_matrix, 3, 3, 3);
    float **xyref_triangle = multiplyMatrices(xyref_matrix, triangle_matrix, 3, 3, 3);
    float **xeqyref_triangle = multiplyMatrices(xeqyref_matrix, triangle_matrix, 3, 3, 3);
    
    for(int i=0; i<3; i++)  {
        glVertex2d((int)xref_triangle[0][i], (int)xref_triangle[1][i]);
    }
    for(int i=0; i<3; i++)  {
        glVertex2d((int)yref_triangle[0][i], (int)yref_triangle[1][i]);
    }
    for(int i=0; i<3; i++)  {
        glVertex2d((int)xyref_triangle[0][i], (int)xyref_triangle[1][i]);
    }
    for(int i=0; i<3; i++)  {
        glVertex2d((int)xeqyref_triangle[0][i], (int)xeqyref_triangle[1][i]);
    }
    glEnd();
}



void display_transforms()   {
    glClear(GL_COLOR_BUFFER_BIT);
    plotDivisionLines();
    
    // int xs[3], ys[3];
    int xs[] = {10, 80, 40};
    int ys[] = {20, 100, 180};
    // printf("\nVertex 1: ");
    // scanf("%d %d", &xs[0], &ys[0]);
    // printf("\nVertex 2: ");
    // scanf("%d %d", &xs[1], &ys[1]);
    // printf("\nVertex 3: ");
    // scanf("%d %d", &xs[2], &ys[2]);
    glColor3f(0.0, 0.0, 1.0);
    plotTriangle(xs, ys);
    glColor3f(1.0, 0.0, 0.0);
    // plotTranslatedTriangle(xs, ys, -100, -50);
    // int x0 = -100;
    // int y0 = -100;
    // int theta = -30;
    // plotRotatedTriangle(xs, ys, 0, 0, theta);
    // plotRotatedTriangle(xs, ys, x0, y0, 45);
    plotScaledTriangle(xs, ys, -10, -20, 1, 2);
    // plotReflectedTriangle(xs, ys);

    glFlush();
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4);
    glLineWidth(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}


int main(int argc, char **argv)  {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);

    // glutCreateWindow("Ex5A - 2D Translation");
    // glutCreateWindow("Ex5B - 2D Rotation");
    glutCreateWindow("Ex5C - 2D Scaling");
    // glutCreateWindow("Ex5D - 2D Reflection");
    glutDisplayFunc(display_transforms);

    init();
    glutMainLoop();
    return 1;
}
