#include <GL/glut.h>
#include <stdio.h>


typedef short* RegionCode;

short trivial_accept(RegionCode code_1, RegionCode code_2)  {
    // all zeros in result implies accept --> return 1
    short result = 0;
    for(int i=0; i<4; i++)  {
        result = result || (code_1[i] || code_2[i]); 
    }
    return !result;
}

short trivial_reject(RegionCode code_1, RegionCode code_2)  {
    // all zeros in result implies reject the reject! --> return 1
    short result = 1;
    for(int i=0; i<4; i++)  {
        result = result || (code_1[i] && code_2[i]); 
    }
    return !result;
}


struct window_constraints   {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
};
typedef struct window_constraints WindowConstraints;

struct point    {
    int x;
    int y;
};
typedef struct point Point;

RegionCode get_region_code(Point pt, WindowConstraints window)    {
    // TBRL
    RegionCode code = (short*)malloc(sizeof(short)*(4));
    
    if(pt.x < window.x_min) {
        code[3] = 1;
        code[2] = 0;
    }
    else if(pt.x > window.x_max)    {
        code[3] = 0;
        code[2] = 1;
    }
    else    {
        code[3] = 0;
        code[2] = 0;
    }

    if(pt.y < window.y_min) {
        code[1] = 1;
        code[0] = 0;
    }
    else if(pt.y > window.y_max)    {
        code[1] = 0;
        code[0] = 1;
    }
    else    {
        code[1] = 0;
        code[0] = 0;
    }

    return code;
    
}


void display_line_clipping()    {
    
    WindowConstraints view_window = {10, 50, 10, 50};
    Point start_pt = {30, 60};
    Point end_pt = {60, 25};

    RegionCode start_pt_code = get_region_code(start_pt, view_window);
    RegionCode end_pt_code = get_region_code(end_pt, view_window);

    printf(">> %d\n", trivial_accept(start_pt_code, end_pt_code));
    printf(">> %d\n", trivial_reject(start_pt_code, end_pt_code));
    short is_clipped = trivial_accept(start_pt_code, end_pt_code) || (
        !trivial_accept(start_pt_code, end_pt_code) && trivial_reject(start_pt_code, end_pt_code)    
    );
    printf("--> %d", is_clipped);
}


void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(2);
    glLineWidth(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);

    glutCreateWindow("Ex7 - Cohen Sutherland Line Clipping");
    glutDisplayFunc(display_line_clipping);

    init();
    glutMainLoop();
    return 0;
}