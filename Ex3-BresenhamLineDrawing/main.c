#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define BUFFER_SIZE 100


void plotDivisionLines()    {
    glBegin(GL_LINES);
    glVertex2d(-320, 0);
    glVertex2d(320, 0);
    glVertex2d(0, -240);
    glVertex2d(0, 240);
    glEnd();
}


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
    renderSpacedBitmapString(x+x_offset, y+y_offset, GLUT_BITMAP_HELVETICA_10, string);
    glFlush();
}


void plotPoint(int x, int y)    {
    glColor3f(0.0, 0, 0.0); // black color
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}


void plotLineBresenham(int start_x, int start_y, int end_x, int end_y)  {
    
    // float slope = (float) (end_y - start_y)/(end_x - start_x);
    // float abs_slope = slope;
    
    // short dx_sign = (start_x <= end_x ? 1 : -1);
    // short dy_sign = (start_y <= end_y ? 1 : -1);
    
    // if(slope>0) {
    //     abs_slope = slope;
    // }
    // else    {
    //     abs_slope = -1 * slope;
    // }

    // float dx, dy;
    // short check_x;
    // if(abs_slope <= 1)  {
    //     dx = (float) (1/abs_slope) * dx_sign;
    //     dy = (float) 1 * dy_sign;
    //     check_x = 0;
    // }
    // else    {
    //     dx = (float) 1 * dx_sign;
    //     dy = (float) abs_slope * dy_sign;
    //     check_x = 1;
    // }

    // printf("\nslope: %f\n", slope);
    // printf("dx: %f, dy: %f\n", dx, dy);
    // printf("check_x: %d\n", check_x);

    // int x_ = start_x;
    // int y_ = start_y;
    // float x_val = start_x;
    // float y_val = start_y;
    // plotPoint(x_, y_);
    // while((check_x && end_x!=x_) || (!check_x && end_y!=y_))    {
    //     x_val += dx;
    //     y_val += dy;
    //     x_ = (int) round(x_val);
    //     y_ = (int) round(y_val);
    //     plotPoint(x_, y_);
    //     // printf("\nx: %d, y: %d", x_, y_);
    //     fflush(stdout);
    // }

    char *point_label = (char*)malloc(sizeof(char)*BUFFER_SIZE);
    sprintf(point_label, "(%d, %d)", start_x, start_y);
    markString(point_label, start_x, start_y, 20, 0);
    sprintf(point_label, "(%d, %d)", end_x, end_y);
    markString(point_label, end_x, end_y, 20, 0);

    int dx = end_x - start_x;
    int dy = end_y - start_x;
    float slope = dy / dx;

    short exchange_xy = 0;
    if(slope>1 || slope<-1) {
        // interchange x and y for computations, 
        // and change back when plotting
        exchange_xy = 1;
        int temp;
        // exchange xs
        temp = start_x;
        start_x = start_y;
        start_y = temp;
        // exchange ys
        temp = end_y;
        end_y = end_x;
        end_x = temp;
        // exchnage ds
        temp = dx;
        dx = dy;
        dy = temp;
    }
    
    int y_delta = 1;
    if(dy < 0)  {
        // bottom to top
        y_delta = -1;
        dy *= -1;
    }

    int x_delta = 1;
    if(dx < 0)  {
        // right to left
        x_delta = -1;
        dx *= -1;
    }

    int x_ = start_x;
    int y_ = start_y;

    printf("\nexchange: %d", exchange_xy);
    printf("\nstart - (%d, %d), end - (%d, %d)", start_x, start_y, end_x, end_y);
    fflush(stdout);
    int p_k = (2*dy) - dx;
    exchange_xy ? plotPoint(y_, x_) : plotPoint(x_, y_);   
    while((!exchange_xy && x_!=end_x) || (exchange_xy && y_!=end_y))  {
        x_ += x_delta;
        if(p_k<0)   {
            exchange_xy ? plotPoint(y_, x_) : plotPoint(x_, y_);
            p_k += 2 * dy;
        }
        else    {
            y_ += y_delta;
            exchange_xy ? plotPoint(y_, x_) : plotPoint(x_, y_);
            p_k += 2*(dy-dx);
        }
        printf("\nx: %d, y: %d", x_, y_);
    }
}


void display()  {
    glClear(GL_COLOR_BUFFER_BIT);
    plotDivisionLines();
    
    int start_x, start_y, end_x, end_y;
    printf("\nEnter Start Coordinates (x y): ");
    scanf(" %d %d", &start_x, &start_y);
    printf("Enter End Coordinates (x y): ");
    scanf(" %d %d", &end_x, &end_y);
    
    // plotLineBresenham(40, 50, 110, 200);
    plotLineBresenham(start_x, start_y, end_x, end_y);
    plotLineBresenham(start_x, -start_y, end_x, -end_y);
    plotLineBresenham(-start_x, start_y, -end_x, end_y);
    plotLineBresenham(-start_x, -start_y, -end_x, -end_y);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(4);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-320.0, 320.0, -240.0, 240.0);
}


int main(int argc,char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Ex3 - Bresenham's Line Drawing");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 1;
}
