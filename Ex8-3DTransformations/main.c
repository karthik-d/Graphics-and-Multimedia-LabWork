#include <GL/glut.h>  
#include <math>

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
            for(int k=0; k<c1; k++)   {
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
            printf("%f ", matrix[i][j]);
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


float** makeScalingMatrix(float sx, float sy)   {
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


void transformAndPlot(double T[4][4], double P[4][1]){
    double new_point[4][1] = {0,0,0, 0};
    
    for (int i=0;i<4;i++){
    
        for (int j=0;j<1;j++){
        
            new_point[i][j] = 0;
            
            for (int k=0;k<4;k++){
                new_point[i][j]+= T[i][k]*P[k][j];
            }
        }
    }
    glVertex3f(new_point[0][0], new_point[1][0], new_point[2][0]);
}

void rotateZ(double x, double y,double z, double theta){
    double angle = theta*3.14/180;
    double rotation_Z_matrix[4][4] = {
        cos(angle), -sin(angle), 0, 0,
        sin(angle), cos(angle), 0,0,
        0,0,1,0,
        0,0,0,1
    };
    
    double point_matrix[4][1] = {x, y, z, 1};
    transformAndPlot(rotation_Z_matrix, point_matrix);
}
 

void display_rotation_translation_scaling() {

    static int theta_vals[3] = {0, 0, 0};
    static int scale_vals[3] = {0, 0, 0};
    static int tr_vals[3] = {0, 0, 0};

    int theta_deltas[3] = {10, 5, 4};
    float scale_deltas[3] = {0.05, 0.1, 0.2};
    int tr_deltas[3] = {10, 5, 6};

    for(int i=0; i<3; i++)  {
        // rotation
        if(theta_vals[i]>360){
            theta_vals[i] -= 360;
        }
        else{
            theta_vals[i] += theta_deltas[i];
        }
        // scaling
        if(scale_vals[i]>2){
            scale_vals[i] = 0.5;
        }
        else{
            scale_vals[i] += scale_deltas[i];
        }
        // translation
        if(tr_vals[i]>100){
            tr_vals[i] = -100;
        }
        else{
            tr_vals[i] += tr_deltas[i];
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW);   
    glLoadIdentity();                
    glTranslatef(0.0f, 0.0f, -7.0f);  

    glBegin(GL_TRIANGLES);

    // Front      
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    rotateZ( 0.0, 1.0, 0.0, theta);
    glColor3f(1.0f, 0.0f, 0.0f);
    rotateZ( -1.0, -1.0, 1.0, theta);
    glColor3f(1.0f, 0.0f, 0.0f);
    rotateZ(1.0, -1.0, 1.0, theta);

    // Right
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    rotateZ(0.0f, 1.0f, 0.0f, theta);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    rotateZ(1.0f, -1.0f, 1.0f, theta);
    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    rotateZ(1.0f, -1.0f, -1.0f, theta);

    // Back
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    rotateZ(0.0f, 1.0f, 0.0f, theta);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    rotateZ(1.0f, -1.0f, -1.0f, theta);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    rotateZ(-1.0f, -1.0f, -1.0f, theta);

    // Left
    glColor3f(1.0f,0.0f,0.0f);       // Red
    rotateZ( 0.0f, 1.0f, 0.0f, theta);
    glColor3f(0.0f,0.0f,1.0f);       // Blue
    rotateZ(-1.0f,-1.0f,-1.0f, theta);
    glColor3f(0.0f,1.0f,0.0f);       // Green
    rotateZ(-1.0f,-1.0f, 1.0f, theta);

    glEnd();   
    glutSwapBuffers(); 
}
 

void Timer(int value){
    glutPostRedisplay();
    glutTimerFunc(value, Timer, value);
}


void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   glClearDepth(1.0f);                   
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);   
   glShadeModel(GL_SMOOTH);  
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}


int main(int argc, char** argv) {
    theta = 0.5;
    glutInit(&argc, argv);           
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);   
    glutInitWindowPosition(50, 50); 
    glutCreateWindow(title);         
    glutDisplayFunc(display);       
    init();
    Timer(500);
    glutMainLoop();                
    return 0;
}
