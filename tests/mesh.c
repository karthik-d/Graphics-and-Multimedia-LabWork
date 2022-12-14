#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>


short perspective = 1;
int x_rotate = 0;
int y_rotate = 0;


void display_render(){
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    // translucency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();

    if(!perspective){
        glOrtho(-2, 2, -2, 2, -2, 2);
    }
    else{
        gluPerspective(120, 1, 0.1, 50);
    }
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    glRotatef(x_rotate, 1, 0, 0);
    glRotatef(y_rotate, 0, 1, 0);

    glColor4f(1, 0, 0, 0.5);
    glutWireCube(1);

    glRasterPos2f(1, 1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'c');
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, 'd');

    glPopMatrix();
    glFlush();    
}


void keyboard_bindings(unsigned char key, int x, int y){
    key = tolower(key);
    switch (key)
    {
        case 'w':
            {
            x_rotate += 5;
            break;
            }
        case 's':
            {
            x_rotate -= 5;
            break;
            }
        case 'd':
            {
            y_rotate += 5;
            break;
            }
        case 'a':
            {
            y_rotate -= 5;
            break;
            }
    }
    glutPostRedisplay();
}


void main(int *argc, char **argv){
    glutInit(&argc, &argv);
    glutCreateWindow("Mesh Projections");

    // glutCle

    glutKeyboardFunc(keyboard_bindings);
    glutDisplayFunc(display_render);

    glutMainLoop();
}