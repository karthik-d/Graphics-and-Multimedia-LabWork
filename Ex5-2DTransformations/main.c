#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

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


void plotDivisionLines()    {
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
}


int** multiplyMatrices(int **m1, int **m2, int r1, int c1, int c2)    {
    // assume compatible matrices
    int **res = (int**)malloc(sizeof(int*)*r1);
    for(int i=0; i<r1; i++) {
        *(res+i) = (int*)malloc(sizeof(int)*c2);
        for(int j=0; j<c2; j++) {
            res[i][j] = 0;
            for(int k=0;k<c1;k++)   {
                res[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
    return res;
}


void displayMatrix(int **matrix, int r, int c)  {
    for(int i=0;i<r;i++)    {
        for(int j=0; j<c; j++)  {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
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


int** makeTriangleMatrix(int *xs, int *ys)  {
    int **res = (int**)malloc(sizeof(int*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (int*)malloc(sizeof(int)*3);
    }
    for(int i=0; i<3; i++) {
        res[0][i] = xs[i];
        res[1][i] = ys[i];
        res[2][i] = 1;
    }
    return res;
}


int** makeTranslationMatrix(int tx, int ty) {
    int **res = (int**)malloc(sizeof(int*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (int*)malloc(sizeof(int)*3);
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


int** makeReflectionMatrix(short along_x) {
    int **res = (int**)malloc(sizeof(int*)*3);
    for(int i=0; i<3; i++) {
        *(res+i) = (int*)malloc(sizeof(int)*3);
        for(int j=0; j<3; j++) {
            if(i==j){
                res[i][j] = 1;
            }
            else{
                res[i][j] = 0;
            }
        }
    }
    if(along_x){
        res[1][1] = -1;
    }
    else{
        res[0][0] = -1;
    }
    return res;
}


void plotTranslatedTriangle(int *xs, int *ys, int tx, int ty)    {
    glBegin(GL_TRIANGLES);
    int **tr_matrix = makeTranslationMatrix(tx, ty);
    displayMatrix(tr_matrix, 3, 3);
    int **triangle_matrix = makeTriangleMatrix(xs, ys);
    displayMatrix(triangle_matrix, 3, 3);
    int **translated_triangle = multiplyMatrices(tr_matrix, triangle_matrix, 3, 3, 3);
    displayMatrix(translated_triangle, 3, 3);
    for(int i=0; i<3; i++)  {
        glVertex2d(translated_triangle[0][i], translated_triangle[1][i]);
    }
    glEnd();
}


void plotReflectedTriangle(int *xs, int *ys)    {
    glBegin(GL_TRIANGLES);
    int **xref_matrix = makeReflectionMatrix(1);
    int **yref_matrix = makeReflectionMatrix(0);
    displayMatrix(xref_matrix, 3, 3);
    int **triangle_matrix = makeTriangleMatrix(xs, ys);
    displayMatrix(triangle_matrix, 3, 3);
    int **xref_triangle = multiplyMatrices(xref_matrix, triangle_matrix, 3, 3, 3);
    displayMatrix(xref_triangle, 3, 3);
    int **yref_triangle = multiplyMatrices(yref_matrix, triangle_matrix, 3, 3, 3);
    for(int i=0; i<3; i++)  {
        glVertex2d(xref_triangle[0][i], xref_triangle[1][i]);
        glVertex2d(yref_triangle[0][i], yref_triangle[1][i]);
    }
    glEnd();
}



void display_transforms()   {
    glClear(GL_COLOR_BUFFER_BIT);
    plotDivisionLines();
    
    int xs[3], ys[3];
    printf("\nVertex 1: ");
    scanf("%d %d", &xs[0], &ys[0]);
    printf("\nVertex 2: ");
    scanf("%d %d", &xs[1], &ys[1]);
    printf("\nVertex 3: ");
    scanf("%d %d", &xs[2], &ys[2]);
    plotTriangle(xs, ys);
    plotTranslatedTriangle(xs, ys, -100, -50);
    plotReflectedTriangle(xs, ys);

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

    glutCreateWindow("Ex5A - 2D Translation");
    glutDisplayFunc(display_transforms);

    init();
    glutMainLoop();
    return 1;
}
