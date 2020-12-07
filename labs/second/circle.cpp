

#include<iostream>
#include<GL/freeglut.h>
#include<math.h>
using std::cout;
using std::endl;
#define CIRCLERAD 0.30f
#define RIGHT_END_OF_MAP 1.00f
#define LEFT_END_OF_MAP 0.00f
#define COLOUR_DEPTH 0.01f
#define NOON  0.0000000f
#define RAD = 0.1

size_t dot_count = 15;
float x  = LEFT_END_OF_MAP - CIRCLERAD; 
float y(0.8f);
float colour_depth = COLOUR_DEPTH;
bool sun_up = true;

bool day = true;
int WindW, WindH;
float x_sun = x;
float y_sun = y;
double rad = 0.1;
float twicePi = 2.0 * 3.142;

GLfloat sun []= {/*x,y coords of dot}*/
//sun
-1.2,0.8,//1 (right end coords)
-1.20865,0.840679,//2
-1.23309,0.874322,//3
-1.26911,0.895111,//4
-1.31047,0.89945,//5
-1.35002,0.886589,//6
-1.38092,0.858752,//7
-1.39782,0.820754,//8
-1.39781,0.779166,//9 (left end coords)
-1.38087,0.741182,//10
-1.34995,0.71337,//11
-1.31039,0.700542,//12
-1.26904,0.704915,//13
-1.23303,0.725733,//14
-1.20861,0.759396,//15
};
GLfloat sun_start []= {/*x,y coords of dot}*/
//sun
-1.2,0.8,//1 (right end coords)
-1.20865,0.840679,//2
-1.23309,0.874322,//3
-1.26911,0.895111,//4
-1.31047,0.89945,//5
-1.35002,0.886589,//6
-1.38092,0.858752,//7
-1.39782,0.820754,//8
-1.39781,0.779166,//9 (left end coords)
-1.38087,0.741182,//10
-1.34995,0.71337,//11
-1.31039,0.700542,//12
-1.26904,0.704915,//13
-1.23303,0.725733,//14
-1.20861,0.759396,//15
};

GLfloat moon []= {/*x,y coords of dot}*/
-1.19, 0.81, 
-1.19865, 0.850679, 
-1.22309, 0.884322, 
-1.25911, 0.905111, 
-1.30047, 0.90945, 
-1.34002, 0.896589, 
-1.37092, 0.868752, 
-1.38782, 0.830754, 
-1.38781, 0.789166, 
-1.37087, 0.751182, 
-1.33995, 0.72337, 
-1.30039, 0.710542, 
-1.25904, 0.714915, 
-1.22303, 0.735733
};

GLubyte moon_colors[] = {
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
	0,0,0,
};
GLubyte sun_colors[] = {
//sun
 	255,219,0,  
	255,219,0,
	255,219,0,
	255,219,0,  
	255,219,0,
	255,219,0,
	255,219,0,
	255,219,0,
	255,219,0,
	255,219,0,
	255,219,0,	
	255,219,0,
	255,219,0,
	255,219,0,  
	255,219,0,
};

GLfloat vertex[] = {//x,y coords of dot
//ground
-1.0f, -1.0f, -1.0f, -0.1f, 1.0f, -0.1f, 1.0f, -1.0f,

//wall
0.2f, -0.5f, 0.2f, 0.1f, -0.2f, 0.1f, -0.2f, -0.5f,
//door
0.1f, -0.2f,-0.1f, -0.2f, -0.1f, -0.5f, 0.1f, -0.5f,
//window 
0.1f, 0.0f,-0.1f, 0.0f,- 0.1f, -0.1f, 0.1f, -0.1f,
//roof
0.2f, 0.1f,-0.2f, 0.1f,0.0f, 0.5f
};

GLubyte colors[] = {

0,67,33,
0,67,33,
0,67,33,
0,67,33,

178,34,34,
178,34,34,
178,34,34,
178,34,34,

154, 4, 41,
154, 4, 41,
154, 4, 41,
154, 4, 41,

255,255,0,
255,255,0,
255,255,0,
255,255,0,

169, 13, 72,
169, 13, 72,
169, 13, 72
};



void display(){
 

	

	

	if(day){
	glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f * colour_depth,0.8f * colour_depth,0.8f*colour_depth,0.0f);
   	glEnableClientState(GL_VERTEX_ARRAY);	
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, vertex);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);
		
	glDrawArrays(GL_QUADS, 0, 16);	
    glDrawArrays(GL_TRIANGLES, 16,3 );
    //glDrawArrays(GL_POLYGON, 37,dot_count );
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);	
		glEnableClientState(GL_VERTEX_ARRAY);	
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, sun);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, sun_colors);

    	glDrawArrays(GL_POLYGON,0,15);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glutSwapBuffers();
		for(int i = 0; i<30; i++){
			if(i%2 == 0)
			sun[i] += 0.02; 
		}

		
		x = sun[0];
		if( RIGHT_END_OF_MAP + CIRCLERAD - std::abs(x) < 0.00f){
            std::cout<< std::endl<<"NIGHT"<<std::endl;
            x = LEFT_END_OF_MAP - CIRCLERAD;
            day = false;
			for(int i =0; i<30; i++)
				sun[i] = sun_start[i];
		

        
        }
		else if( (x + NOON > NOON) && (sun_up == true) ) {
            std::cout<<"NOON"<<std::endl;
            sun_up = false;
			colour_depth = 1.0;
        }
		if(sun_up)
			colour_depth += COLOUR_DEPTH;
		else
			colour_depth -= COLOUR_DEPTH;

	}
	else{//night
		
		glClear(GL_COLOR_BUFFER_BIT);
    	glClearColor(0.0f,0.0f,0.0f,0.0f);
   		glEnableClientState(GL_VERTEX_ARRAY);	
		glEnableClientState(GL_COLOR_ARRAY);
	
		glVertexPointer(2, GL_FLOAT, 0, vertex);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);
		
		glDrawArrays(GL_QUADS, 0, 16);	
    	glDrawArrays(GL_TRIANGLES, 16,3 );
		cout<<" "<<sun[0];
		glEnableClientState(GL_VERTEX_ARRAY);	
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, sun);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, sun_colors);
		glDrawArrays(GL_POLYGON,0,15);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glEnableClientState(GL_VERTEX_ARRAY);	
		glEnableClientState(GL_COLOR_ARRAY);
		glVertexPointer(2,GL_FLOAT,0, moon);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, moon_colors);
		glDrawArrays(GL_POLYGON,0,15);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glutSwapBuffers();
		for(int i = 0; i<30; i++){
			if(i%2 == 0){
				sun[i] += 0.02; 
				moon[i]+= 0.02;
				x = sun[i];
			}
		}
		if( RIGHT_END_OF_MAP + CIRCLERAD - std::abs(x) < 0.00f){
            std::cout<< std::endl<<"DAY"<<std::endl;
            x = LEFT_END_OF_MAP - CIRCLERAD;
            sun_up = true;
            day = true;
			for(int i =0; i<30; i++){
				sun[i] = sun_start[i];
				if(i%2 == 0)
					moon[i] = sun[i] +0.02f;
				else
					moon[i]= sun[i];
		}
    }
		
	

    
	
}
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