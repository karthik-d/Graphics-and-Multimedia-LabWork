//
//  main.cpp
//  GML
//
//  Created by csea39 on 10/20/22.
//

#include <GLUT/glut.h>  // GLUT, include glu.h and gl.h
#include<cmath>
double theta;
/* Global variables */
char title[] = "3D Shapes";
 
/* Initialize OpenGL Graphics */
void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
   glClearDepth(1.0f);                   // Set background depth to farthest
   glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
   glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
   glShadeModel(GL_SMOOTH);   // Enable smooth shading
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
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



 
/* Handler for window-repaint event. Called back when the window first appears and
   whenever the window needs to be re-painted. */
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
    theta+=5;
    // Render a pyramid consists of 4 triangles
    // Move left and into the screen
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(0.0f, 0.0f, -7.0f);  // Move right and into the screen
 
   glBegin(GL_TRIANGLES);
    // Begin drawing the pyramid with 4 triangles
    
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
   
    glEnd();   // Done drawing the pyramid
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}
 
/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height.
*/
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
   // Compute aspect ratio of the new window
   if (height == 0) height = 1;                // To prevent divide by 0
   GLfloat aspect = (GLfloat)width / (GLfloat)height;
 
   // Set the viewport to cover the new window
   glViewport(0, 0, width, height);
 
   // Set the aspect ratio of the clipping volume to match the viewport
   glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
   glLoadIdentity();             // Reset
   // Enable perspective projection with fovy, aspect, zNear and zFar
   gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
 
void Timer(int value){
    glutPostRedisplay();
    glutTimerFunc(500, Timer, 0);
}


/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    theta = 0.5;
   glutInit(&argc, argv);            // Initialize GLUT
   glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
   glutInitWindowSize(640, 480);   // Set the window's initial width & height
   glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
   glutCreateWindow(title);          // Create window with the given title
   glutDisplayFunc(display);       // Register callback handler for window re-paint event
   glutReshapeFunc(reshape);       // Register callback handler for window re-size event
   initGL();// Our own OpenGL initialization
    Timer(0);
   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
