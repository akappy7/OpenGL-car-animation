#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "Background.h"

#define GRASS 0, .75, .4
#define WIDTH 800
#define LENGTH 800
#define MAX 8000
#define MIN -5000
#define SPACE 400

Background::Background(){

}

void Background::drawTrees(){

	for(int ii=MAX; ii>=MIN; ii-=500)
	{	

	glPushMatrix();{
		glColor3f(1,1,1);
		glTranslatef(ii,250,0);
		glScalef(1,1,.5);
		GLUquadricObj *obj= gluNewQuadric();
		
		gluCylinder(obj,4,2,100,10,8);
			}glPopMatrix();
	}	
	for(int ii=MAX; ii>=MIN; ii-=500)
	{	

	glPushMatrix();{
		glColor3f(1,1,1);
		glTranslatef(200 + ii,-90,0);
		glScalef(1,1,.5);
		GLUquadricObj *obj= gluNewQuadric();
		
		gluCylinder(obj,4,2,100,10,8);
			}glPopMatrix();
	}	
int f = 0;
int j = -150;
for(int i=MAX; i>=MIN; i-=SPACE/2){	
		glPushMatrix();
		glColor3f(.75,.4,.2);
		if(f == 0){
			j = -300;
			f = 1;
		}
		else if(f == 1){
			j = -150;
			f = 2;
		}
		else{
			j = -450;
			f = 0;
		}
		glTranslatef(i, j ,0);
		glScalef(1,1,1.5);
		GLUquadricObj *obj= gluNewQuadric();
		gluCylinder(obj,4,2,100,10,8);
		glPopMatrix();

		glPushMatrix();
		glColor3f(.1,.5,.1);
     	glTranslatef(i,j,50);
		glScalef(15,15,20);

		glTranslatef(0,0,5);
		glutSolidSphere(3,50,20);
		glPopMatrix();
	}
	j = 350;
	for(int i=MAX; i>=MIN; i-=SPACE/2){	
		glPushMatrix();
		glColor3f(.75,.4,.2);
		if(f == 0){
			j = 500;
			f = 1;
		}
		else if(f == 1){
			j = 650;
			f = 2;
		}
		else{
			j = 350;
			f = 0;
		}
		glTranslatef(i, j ,0);
		glScalef(1,1,1.5);
		GLUquadricObj *obj= gluNewQuadric();
		gluCylinder(obj,4,2,100,10,8);
		glPopMatrix();

		glPushMatrix();
		glColor3f(.1,.5,.1);
     	glTranslatef(i,j,50);
		glScalef(15,15,20);

		glTranslatef(0,0,5);
		glutSolidSphere(3,50,20);
		glPopMatrix();
	}		

}

void Background::GenericQuad(float r, float g, float b, int xx, int xy, int yx, int yy, int z){
	glColor3f(r, g, b);
	glBegin(GL_QUADS);{
		glVertex3f(xx,xy,z);
		glVertex3f(yy, xy,z);
		glVertex3f(yy, yx,z);
		glVertex3f(xx, yx,z);
	}glEnd();
}

void Background::drawField(){
	GenericQuad(GRASS, MIN, -90, -1000, MAX, 0);
	GenericQuad(GRASS, MIN, 250, 1000, MAX, 0);
}

void Background::drawRoad(){
	GenericQuad(0.1, 0.1, 0.1, MIN, -100, 260, MAX, 1);

	for(int x = MIN; x < MAX; x+=100){
		GenericQuad(1, 1, 0, x, 70, 75, x+50, 2);
		GenericQuad(1, 1, 0, x, 80, 85, x+50, 2);
	}

	GenericQuad(.8, .8, .8, MIN, -75, -80, MAX, 2);
	GenericQuad(.8, .8, .8, MIN, 235, 240, MAX, 2);
    
}



