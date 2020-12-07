#include<GL/freeglut.h>
#include<math.h>
#include <iostream>

#define CIRCLERAD 0.30f
#define RIGHT_END_OF_MAP 1.00f
#define LEFT_END_OF_MAP -1.00f
#define COLOUR_DEPTH 0.01f
#define NOON  0.0000000f

float x  = LEFT_END_OF_MAP - CIRCLERAD; 
float y(0.8f);
float colour_depth = COLOUR_DEPTH;
bool sun_up = true;
bool day = true;
int WindW, WindH;

void drawCircle(float x , float y, int r , int g , int b, int dot_count ){
    double rad = 0.1;
    double twicePi = 2.0 * 3.142;
    glColor3ub(r,g,b);
    glBegin(GL_POLYGON);
    for (int i= 0 ; i < dot_count; i++){
        glVertex2f(x +(rad *cos(i * twicePi/dot_count)), y +(rad *sin(i * twicePi/dot_count)));
        std::cout<<x +(rad *cos(i * twicePi/dot_count))<<","<<y +(rad *sin(i * twicePi/dot_count))<<std::endl;
    }
    glEnd();
    exit(0);
}

void display(){
    
   // glClearColor(0.0f * colour_depth,0.8f * colour_depth,0.8f*colour_depth,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3ub(0,67,33);//земля
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f,-1.0f);
        glVertex2f(-1.0f, -0.1f);
        glVertex2f(1.0f,-0.1f);
        glVertex2f(1.0f,-1.0f);
    glEnd();
    //СТРОИМ ДОМ
    glColor3ub(178,34,34);//стена
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, -0.5f);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.2f, - 0.5f);
    glEnd();
    glColor3ub(169, 13, 72);//крыша
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(0.0f, 0.5f);
    glEnd();
        
    glColor3ub(154, 4, 41);//дверь
    glBegin(GL_POLYGON);
        glVertex2f( 0.1f, -0.2f);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(- 0.1f, -0.5f);
        glVertex2f( 0.1f, -0.5f);
    glEnd();

//рисуем день
    if( day == true ) {
        glClearColor(0.0f * colour_depth,0.8f * colour_depth,0.8f*colour_depth,0.0f);
        glColor3f(0.0f * colour_depth,0.8f * colour_depth,0.8f*colour_depth);
        glBegin(GL_POLYGON);
            glVertex2f( 0.1f, 0.0f);
            glVertex2f(-0.1f, 0.0f);
            glVertex2f(- 0.1f, -0.1f);
            glVertex2f( 0.1f, -0.1f);
        glEnd();
        drawCircle(x, y, 255, 255 ,0 , 15);
        if( RIGHT_END_OF_MAP + CIRCLERAD - std::abs(x) < 0.00f){
            std::cout<< std::endl<<"BANG"<<std::endl;
            x = LEFT_END_OF_MAP - CIRCLERAD;
            sun_up = true;
            day = false;
        
        }
        else if( (x + NOON > NOON) && (sun_up == true) ) {
            std::cout<<"NOON"<<std::endl;
            sun_up = false;
        }

        else if(sun_up == true)
            colour_depth += COLOUR_DEPTH;
        else
            colour_depth -= COLOUR_DEPTH;
        x+=0.01f;
        //std::cout<<x<< " ";
    }
 //рисуем ночь   
    else {
        glClearColor(0.0f ,0.0f,0.0 *colour_depth,0.0f);
        glColor3ub(255,255,0);
        glBegin(GL_POLYGON);
            glVertex2f( 0.1f, 0.0f);
            glVertex2f(-0.1f, 0.0f);
            glVertex2f(- 0.1f, -0.1f);
            glVertex2f( 0.1f, -0.1f);
        glEnd();

        std::cout<<"NIGHT"<<std::endl;;
        drawCircle(x, y, 255, 255 ,0 , 15);
        drawCircle(x + 0.02f, y,0.0f * colour_depth,0.8f * colour_depth,0.8f*colour_depth,15);
        x+= 0.01f;
        if( RIGHT_END_OF_MAP + CIRCLERAD - std::abs(x) < 0.00f){
            std::cout<< std::endl<<"BANG"<<std::endl;
            x = LEFT_END_OF_MAP - CIRCLERAD;
            sun_up = true;
            day = true;
        }

    }
    glutSwapBuffers();
    
} 
void Reshape(int width, int height) // Reshape function
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  
  WindW = width;
  WindH = height;
}

int main(int argc, char** argv) {
    WindW =400;
    WindH = 400;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WindH,WindW);
    glutInitWindowPosition(WindH,WindW);
    glutCreateWindow("Laba2");
    glutReshapeFunc(Reshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
   
    glutMainLoop();

return 0;
}
