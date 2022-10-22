#include <GL/glut.h>  
#include <math>


void init() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
   glClearDepth(1.0f);                   
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL);   
   glShadeModel(GL_SMOOTH);  
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
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

    static int theta = 0;
    static int scale_x = 0;
    static int scale_y = 0;
    static int scale_z = 0;
    static int tr_x = 0;
    static int tr_y = 0;
    static int tr_z = 0;

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
 

void reshape(GLsizei width, GLsizei height) {  
    if (height == 0) height = 1;               
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();            
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 

void Timer(int value){
    glutPostRedisplay();
    glutTimerFunc(500, Timer, 0);
}


int main(int argc, char** argv) {
    theta = 0.5;
    glutInit(&argc, argv);           
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);   
    glutInitWindowPosition(50, 50); 
    glutCreateWindow(title);         
    glutDisplayFunc(display);       
    glutReshapeFunc(reshape);       
    initGL();
    Timer(0);
    glutMainLoop();                
    return 0;
}
