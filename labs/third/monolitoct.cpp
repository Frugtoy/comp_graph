#define STB_IMAGE_IMPLEMENTATION
#include<GL/glut.h>
#include<GL/gl.h>
#include<cmath>
#include<iostream>
#include "./third_party/stb_image.h"


using std::cin;
using std::cout;

//funk list
void drawOct( float normX , float normY, float normZ, float normH);
void drawSphere();
void reshape(int WIDTH, int HEIGH);
void init();
void movement_logic();
void button_pressed(int button, int x_curs_pos, int y_curs_pos);
void load_textures();

void drawSlizedOct();
//setup screen params
GLfloat screenHeight = 450.0;
GLfloat screenWidth = 450.0;

//oct coords
GLfloat octX = 0.0;//x s segment
GLfloat octY = 0.0;//y s segment
GLfloat octZ = 0.0;//z s segment
GLfloat octH = 200.0;

//normals
GLfloat octNormX = -0.04;
GLfloat octNormY = -0.04;
GLfloat octNormZ = -0.04;
GLfloat octNormH = -0.4;

//oct_rotation 
GLfloat rotateOctX= 0.0;
GLfloat rotateOctY = 0.0;
GLfloat rotateOctZ = 0.0;

//sphere_lightness_rotation
GLfloat sphereLightnessX = 0.0;
GLfloat sphereLightnessZ = -1.0;

GLint speed_of_oct_rotation = 3;
GLint speed_of_sphere_rotation = 1;


///textures
struct text_img {
	unsigned char * data;
	int sizeX,sizeY,n;
};
char text_name[8][11]{
	"aq.png",  "bl.png" , "grad.png", "green.png",   "org.png",  "red.png",  "vi.png",  "yel.png"
};

GLuint textures[8];
int texsum = sizeof(textures)/sizeof(textures[0]);

//oct rotation cases
enum oct_rotation{
	non = 0,
	oct_x_up_rotation,
	oct_x_down_rotation,
	oct_y_left_rotation,
	oct_y_right_rotation
};

//sphere rotation cases
enum sphere_rotation{
	nope = 0,
	sphere_left_rotation,
	sphere_right_rotation
};

//presets
bool oct_is_multicolored = true;
bool oct_is_multitextured = false; 
bool oct_is_textured = false;
bool oct_is_slized = false;
bool light = true;
bool blend = false;

oct_rotation oct_rot = non;
sphere_rotation sphere_rot = nope;
GLubyte slized_vertex_color[][3]{
		// красный
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,

	255, 0, 0,
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,

	255, 0, 0,
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,

	255, 0, 0,
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,

	255, 0, 0,
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,

	255, 0, 0,
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,

	255, 0, 0,
	255, 0, 0,
	255, 0, 0,
	255, 0, 0,


	// оранжевый
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,

	255, 89, 0,
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,

	255, 89, 0,
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,

	255, 89, 0,
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,

	255, 89, 0,
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,

	255, 89, 0,
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,

	255, 89, 0,
	255, 89, 0,
	255, 89, 0,
	255, 89, 0,

	// жёлтый
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,

	255, 255, 0,
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,

	255, 255, 0,
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,

	255, 255, 0,
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,

	255, 255, 0,
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,

	255, 255, 0,
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,

	255, 255, 0,
	255, 255, 0,
	255, 255, 0,
	255, 255, 0,


	// зелёный
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,

	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,

	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,

	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,

	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,

	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,

	0, 255, 0,
	0, 255, 0,
	0, 255, 0,
	0, 255, 0,

	// голубой
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,

	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,

	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,

	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,

	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,

	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,

	0, 255, 255,
	0, 255, 255,
	0, 255, 255,
	0, 255, 255,

	// синий
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,

	0, 0, 255,
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,

	0, 0, 255,
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,

	0, 0, 255,
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,

	0, 0, 255,
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,

	0, 0, 255,
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,

	0, 0, 255,
	0, 0, 255,
	0, 0, 255,
	0, 0, 255,

	// фиолетовый
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,

	255, 0, 255,
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,

	255, 0, 255,
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,

	255, 0, 255,
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,

	255, 0, 255,
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,

	255, 0, 255,
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,

	255, 0, 255,
	255, 0, 255,
	255, 0, 255,
	255, 0, 255,


	// градиент
	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	100, 100, 100,

	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	100, 100, 100,

	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	100, 100, 100,

	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	100, 100, 100,

	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	100, 100, 100,

	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	100, 100, 100,

	255, 0, 0,
	0, 255, 0,
	0, 0, 255,
	100, 100, 100,

};


void drawOct( float normX , float normY, float normZ, float normH){
//bottom front left red
    glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_POLYGON);
	
		if(oct_is_multicolored)
        	glColor3f(1.0, 0.0, 0.0);

        glTexCoord2f(1.0,1.0);
        glNormal3f(-octNormX, octNormH, octNormZ);
        glVertex3f(-octX, -octH, octZ);
        
        glTexCoord2f(1.0,0.0);
        glNormal3f(-octNormX, -octNormY, -octNormH);
        glVertex3f(-octX, -octY, octH);
       
        glTexCoord2f(0.0,0.0);
        glNormal3f(octNormH, -octNormY, octNormZ);
        glVertex3f(-octH, -octY, octZ);
	glEnd();
	
	//bottom front right orange
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_POLYGON);
    	if(oct_is_multicolored)
			glColor3f(1.0, 0.5, 0.0);
        
	    glTexCoord2f(1.0,0.0);
	    glNormal3f(-octNormH, octNormY, octNormZ);
	    glVertex3f(octH, -octY, octZ);

	    glTexCoord2f(0.0,1.0);
	    glNormal3f(octNormX, -octNormY, -octNormH);
	    glVertex3f(octX, -octY, octH);

	    glTexCoord2f(0.0,0.0);
	    glNormal3f(octNormX, octNormH, octNormZ);
	    glVertex3f(octX, -octH, octZ);
	glEnd();
	
	//bottom back right yellow
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_POLYGON);
	
        if(oct_is_multicolored)
        	glColor3f(1.0, 1.0, 0.0);     
	    
		glTexCoord2f(1.0,0.0);
	    glNormal3f(octNormH, -octNormY, -octNormZ);
	    glVertex3f(octH, -octY, -octZ);

	    glTexCoord2f(0.0,0.0);
	    glNormal3f(-octNormX, -octNormY, -octNormH);
	    glVertex3f(octX, -octY, -octH);

	    glTexCoord2f(0.0,1.0);
	    glNormal3f(-octNormX, -octNormH, -octNormZ);
	    glVertex3f(octX, -octH, -octZ);
	glEnd();



	//bottom back left green
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_POLYGON);
	
		if(oct_is_multicolored)
        	glColor3f(0.0, 1.0, 0.0);

	    glTexCoord2f(1.0,0.0);
	    glNormal3f(-octNormX, -octNormH, -octNormZ);
        glVertex3f(-octX, -octH, -octZ);

	    glTexCoord2f(0.0,0.0);
        glNormal3f(octNormX, -octNormY, -octNormH);
	    glVertex3f(-octX, -octY, -octH);

	    glTexCoord2f(0.0,1.0);
	    glNormal3f(-octNormH, -octNormY, -octNormZ);
	    glVertex3f(-octH, -octY, -octZ);
	glEnd();

	//top back left light-blue
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_POLYGON);
	
	    if(oct_is_multicolored)
        	glColor3f(0.0, 0.5, 1.0);
              
	   	glTexCoord2f(1.0,0.0);
	    glNormal3f(-octNormX, -octNormH, -octNormZ);
	    glVertex3f(-octX, octH, -octZ);

	    glTexCoord2f(0.0,0.0);
        glNormal3f(-octNormX, -octNormY, octNormH);
	    glVertex3f(-octX, octY, -octH);

	    glTexCoord2f(0.0,1.0);
	    glNormal3f(octNormH, octNormY, -octNormZ);
	    glVertex3f(-octH, octY, -octZ);
	glEnd();

	//top front left blue
	glBindTexture(GL_TEXTURE_2D, textures[5]); 
	glBegin(GL_POLYGON);
	  
        if(oct_is_multicolored)
        	glColor3f(0.0, 0.0, 1.0);
        
		
	    glTexCoord2f(0.0,0.0);
	    glNormal3f(-octNormX, octNormH, octNormZ);
	    glVertex3f(-octX, octH, octZ);

	    glTexCoord2f(1.0,0.0);
	    glNormal3f(-octNormX, octNormY, octNormH);
	    glVertex3f(-octX, octY, octH);

	   glTexCoord2f(1.0,1.0);
	    glNormal3f(-octNormH, octNormY, octNormZ);
	    glVertex3f(-octH, octY, octZ);
	glEnd();

	//top front right violent
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glBegin(GL_POLYGON);
	
		if(oct_is_multicolored)
        glColor3f(0.502, 0.0, 0.502);
       
	    glTexCoord2f(1.0,0.0);
	    glNormal3f(octNormH, octNormY, octNormZ);
	    glVertex3f(octH, octY, octZ);

	    glTexCoord2f(1.0,1.0);
	    glNormal3f(octNormX, octNormY, octNormH);
	    glVertex3f(octX, octY, octH);

	    glTexCoord2f(0.0,1.0);
	    glNormal3f(octNormX, octNormH, octNormZ);
	    glVertex3f(octX, octH, octZ);
	glEnd();

	//top back right gradient
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	glBegin(GL_POLYGON);
	
		if(oct_is_multicolored)
        	glColor3f(1.0, 0.0, 0.0);
    	
	    glTexCoord2f(1.0,0.0);
	    glNormal3f(-octNormH, octNormY, -octNormZ);
	    glVertex3f(octH, octY, -octZ);
	
		if(oct_is_multicolored)
	   		glColor3f(0.0, 1.0, 0.0);
    	
		glTexCoord2f(1.0,1.0);
	    glNormal3f(octNormX, octNormY, octNormH);
	    glVertex3f(octX, octY, -octH);
		
		if(oct_is_multicolored)
	    	glColor3f(0.0, 0.0, 1.0);
        
		
		glTexCoord2f(0.0,0.0);
	    glNormal3f(octNormX, -octNormH, -octNormZ);
	    glVertex3f(octX, octH, -octZ);

	glEnd();

}

void drawSlizedOct(){

	int dot = 0;//color arr
	float semi_phi = 3.1415 / 2;
	float x, y, z = 0.0;
	float segment = 0.053;

	for (int y_segment  = 1; y_segment  <= 2; y_segment ++) {
		for (int semi_phi_sector= 0; semi_phi_sector< 4; semi_phi_sector++) {
			for (int i = 0; i < 21; i += 3) {
			x, y, z = 0.0;
			glBegin(GL_POLYGON);
			x = (1 - (segment  * i)) * sin( semi_phi * semi_phi_sector ) * octH;
			if (y_segment  == 1) {
				y = segment  * i * octH;
			}
			else {
				y = -segment  * i * octH;
			}
			z = (1 - (segment  * i)) * cos( semi_phi * semi_phi_sector )*octH;
			glColor3ub(slized_vertex_color[dot][0],slized_vertex_color[dot][1],slized_vertex_color[dot][2]);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);

			dot++;
			x = (1 - (segment  * i)) * sin(semi_phi * (semi_phi_sector+ 1))*octH;
			if (y_segment  == 1) {
				y = segment  * i *octH;
			}
			else {
				y = -segment  * i *octH;
			}
			z = (1 - (segment  * i)) * cos(semi_phi * (semi_phi_sector+ 1))*octH;

			glColor3ub(slized_vertex_color[dot][0],slized_vertex_color[dot][1],slized_vertex_color[dot][2]);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);

			dot++;
			x = (1 - segment  * (i + 1)) * sin(semi_phi * (semi_phi_sector+ 1))*octH;
			if (y_segment  == 1) {
				y = segment  * (i + 1) * octH;
			}
			else {
				y = -segment  * (i + 1) * octH;
			}
			z = (1 - segment  * (i + 1)) * cos(semi_phi * (semi_phi_sector+ 1))* octH;
			glColor3ub(slized_vertex_color[dot][0],slized_vertex_color[dot][1],slized_vertex_color[dot][2]);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
			dot++;
			x = (1 - segment  * (i + 1)) * sin(semi_phi * semi_phi_sector ) * octH;
			if (y_segment  == 1) {
				y = segment  * (i + 1)*octH;
			}
			else {
				y = -segment  * (i + 1)*octH;
			}
			z = (1 - segment  * (i + 1)) * cos(semi_phi * semi_phi_sector ) * octH;
			glColor3ub(slized_vertex_color[dot][0],slized_vertex_color[dot][1],slized_vertex_color[dot][2]);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
			dot++;
			glEnd();
			}
		}
	}

}

void drawSphere(){
	glColor3f(1.0,1.0,1.0);
	glTranslatef(0.0,0.0,240.0);
	glutWireSphere(20.0,10.0,10.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(oct_is_slized){

		glPushMatrix();
        glRotatef(rotateOctX, 1.0, 0.0, 0.0);
        glRotatef(rotateOctY, 0.0, 1.0, 0.0);
        drawSlizedOct();
		movement_logic();
        glPopMatrix();
    }
	else {
		if(blend){
			glEnable(GL_BLEND);
			glDepthMask(GL_FALSE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		}
		if(oct_is_multicolored)
		{
			glPushMatrix();
			glRotatef(rotateOctX, 1.0, 0.0, 0.0);
			glRotatef(rotateOctY, 0.0, 1.0, 0.0);
			drawOct(octNormX, octNormY, octNormZ, octNormH);
			movement_logic();
			glPopMatrix();
		}

		else 
		{
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			glRotatef(rotateOctX, 1.0, 0.0, 0.0);
			glRotatef(rotateOctY, 0.0, 1.0, 0.0);
			drawOct(octNormX, octNormY, octNormZ, octNormH);
			movement_logic();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		
		}
		if(blend){
			glDepthMask(GL_TRUE);
			glDisable(GL_BLEND);
		}
	}

	
	glPushMatrix();
	glRotatef(sphereLightnessZ,0.0,1.0,0.0);
	drawSphere();
	GLfloat sphere_lightness[] = {0.0,0.0,190,0.0};
	glLightfv(GL_LIGHT0, GL_POSITION, sphere_lightness);
	glPopMatrix();
    glutSwapBuffers();
	if(light) glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);
}

void reshape(int WIDTH, int HEIGH)
{
    if (HEIGH == 0)
        {
            HEIGH = 1;
        }

	glViewport(0, 0, (GLsizei)WIDTH, (GLsizei)HEIGH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2, -HEIGH / 2, HEIGH / 2, -450.0, 450.0);
	glMatrixMode(GL_MODELVIEW);

	display();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	GLfloat outside_light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, outside_light_diffuse);
	
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_NORMALIZE);
	load_textures();
}

void movement_logic(){
	switch(oct_rot){
		case oct_y_right_rotation:
			rotateOctY+=speed_of_oct_rotation;
			break;
		case oct_y_left_rotation:
			rotateOctY-=speed_of_oct_rotation;
			break;
		case oct_x_up_rotation:
			rotateOctX+=speed_of_oct_rotation;
			break;
		case oct_x_down_rotation:
			rotateOctX-=speed_of_oct_rotation;
			break;
		
		default:
			break;
	}
	switch (sphere_rot)
	{
	case sphere_left_rotation:
		if(sphereLightnessZ >=0)
			sphereLightnessZ -= speed_of_sphere_rotation;
		else sphereLightnessZ = 360;
		break;
	case sphere_right_rotation:
		if(sphereLightnessZ >=0)
			sphereLightnessZ += speed_of_sphere_rotation;
		else sphereLightnessZ = 360;
	default:
		break;
	}
	glutPostRedisplay();
}

void button_pressed(int button, int x_curs_pos, int y_curs_pos){
	switch(button){
		case GLUT_KEY_RIGHT:

			if(oct_rot == non ){
				oct_rot = oct_y_right_rotation;
			}
			else  oct_rot = non;
			break;
		case GLUT_KEY_LEFT:
	
			if(oct_rot == non ){
				oct_rot = oct_y_left_rotation;
			}
			else oct_rot = non;
			
			break;
		case GLUT_KEY_UP:
			if(oct_rot == non ){
				oct_rot = oct_x_up_rotation;
			}
			else oct_rot = non;
			
			break;
		case GLUT_KEY_DOWN:
			if(oct_rot == non ){
				oct_rot = oct_x_down_rotation;
			}
			else oct_rot = non;
			
			break;
		case GLUT_KEY_F1:
			if(sphere_rot == nope)
				sphere_rot = sphere_left_rotation;
			else sphere_rot = nope;
			
			break;
		case GLUT_KEY_F2:
			if(sphere_rot == nope)
				sphere_rot = sphere_right_rotation;
			else sphere_rot = nope;
			break;

		case GLUT_KEY_PAGE_UP:
			octX+=0.6;
			octY+=0.6;
			octZ+=0.6;
			break;
		case GLUT_KEY_PAGE_DOWN:
			if(abs(octX) >= 0.00001){
				octX -=0.6;
				octY -=0.6;
				octZ -=0.6;
			}
			
			break;
		case GLUT_KEY_F3:
			octX=0.0;
			octY=0.0;
			octZ=0.0;
			break;
		case GLUT_KEY_F4:
			if(!oct_is_slized){
				oct_is_multicolored = true;
				oct_is_multitextured = false;
				oct_is_textured = false;
			}
			break;
		case GLUT_KEY_F6:
			if(!oct_is_slized){
				oct_is_multicolored = false;
				oct_is_multitextured =false;
				glEnable(GL_TEXTURE_2D);
				oct_is_textured = true;
				load_textures();
				}
			break;	
		case GLUT_KEY_F7:
			if(!oct_is_slized){
				oct_is_multicolored = false;
				oct_is_multitextured = true;
				glEnable(GL_TEXTURE_2D);
				oct_is_textured = true;
				load_textures();
			}
			break;
		
		case GLUT_KEY_F8:
		if (!oct_is_slized)
				blend=!blend;
			break;
		case GLUT_KEY_F9:
			oct_is_slized =! oct_is_slized;
			if(oct_is_slized){
				oct_is_textured = false;
				oct_is_multicolored = false;
				oct_is_multitextured = false;
			}
			break;
		case GLUT_KEY_F5:
			light = !light;
			break;
		default:
			break;


	}
	glutPostRedisplay();//for future (textures etc)

}

void load_textures()
{ 
	text_img* texture  = new text_img [8];
	
	//size_t texture_pos = 0;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(8, textures);

		for(int i(0), texture_pos(0); i < 8; i++){
			texture[i].data = stbi_load(text_name[texture_pos],&texture[i].sizeX,&texture[i].sizeY,&texture[i].n,STBI_rgb);
			if(texture[i].data == nullptr) {std::cout<<"it's seems some troubles with textures loading\n";exit(0);}
			if(oct_is_multitextured)  
				texture_pos++;
			
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, texture[i].sizeX, texture[i].sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture[i].data);
		}

	delete[] texture;
}

int main(int argc, char **argv)
{
//manual
	std::cout<<"OCT MOVEMENTS: \n"
	<<"RIGHT - rotate oct right\n"
	<<"LEFT - rotate oct left\n"
	<<"UP - rotate oct up\n" 
	<<"DOWN - rotate oct down\n"<<"to stop oct movements press  KEY left,right up or down\n\n"
	<<"PAGE UP - move edges up\n"
	<<"PAGE DOWN - move edges down\n"
	<<"F3 - set edges def position\n\nsphere movements:\n"
	<<"F1 - move sphere left\n"
	<<"F2 - move sphere right\n"
	<<"to stop sphere movements press key F1 or F2\n\n"
	<<"F4 - make oct multicolored\n"
	<<"F5 - switch the lightness ON/OFF\n"
	<<"F6 - make oct monotextured\n"
	<<"F7 - make oct multitextred\n"
	<<"F8 - make oct blend, not blend\n"
	<<"F9 - make oct slized\n";


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(450, 10);
	glutInitWindowSize(screenWidth, screenHeight);
	glutCreateWindow("LAB 3");
	glutDisplayFunc(display);
	init();
	movement_logic();
	glutReshapeFunc(reshape);
	glutSpecialFunc(button_pressed);
	glutMainLoop();

	return 0;
}