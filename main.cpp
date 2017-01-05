#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h> 

#include "tiny_obj_loader.h"

#include "Car.h"
#include "Background.h"

#define WIDTH 800
#define LENGTH 800

using namespace std;


int MainWindow;
int wflag=0;
int last = 0;
int last2 = 0;
int last3 = 0;

Background b=Background();
Car body = Car();
Car backW = Car();
Car frontW = Car();
Car city = Car();
Car sun = Car();
Car city2 = Car();
Car city3 = Car();
Car city4 = Car();

double moveX;
double moveY;

int wheelA= 0;
int sunM= 0;
float sky = 0;

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(.5- sky, .4-sky, .7-sky, 1);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  
  if(sky < .19){
    gluLookAt(5000*cos(1.5) + 0, 50*sin(1.5) + 0, 10,   0+body.moveX,0+body.moveY,0,    0,0,1);
  }
  else if(sky < .25){
  gluLookAt(-400*cos(1.5)+body.moveX, 50*sin(1.5)+body.moveY, 20,   0+body.moveX,0+body.moveY,0,    0,0,1);
  }
  else if(sky < .30){
  gluLookAt(50*cos(1.5)+body.moveX, -150*sin(1.5)+body.moveY, 20,   0+body.moveX,0+body.moveY,20,    0,0,1);
  }
  else if(sky < .35){
    gluLookAt(-1500*cos(1.5)+body.moveX, 40*sin(1.5)+body.moveY, 40,   0+body.moveX,0+body.moveY,30,    0,0,1);
  }
 else if(sky < .55){
    gluLookAt(-4500*cos(1.5)+body.moveX, -300*sin(1.5)+body.moveY+ sky*400, 100,   0+body.moveX,0+body.moveY,100,    0,0,1);
    last = body.moveX;
  }
  else if(sky < .70){
    gluLookAt(-4500*cos(1.5)+last, -10*sin(1.5)+body.moveY, 5,  0+body.moveX,0+body.moveY,30,    0,0,1);
    last3 = body.moveX;
    last2 = 0;
  }
 else if(sky < .85){
    gluLookAt(-4500*cos(1.5)+last, -10*sin(1.5)+body.moveY, 5,  0+last3,0+body.moveY, 10 + last2 *100 ,    0,0,1);
    last2+=1;
  }
  if(sky > .85){
    cout<<"Thank you for watching!"<<endl;
    exit(1);
  }

	glMatrixMode(GL_MODELVIEW);
   glEnable(GL_LIGHTING);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHT0);


GLfloat light_position1[] = { 10000.0, 1.0, 20.00, 0.0 };
glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
  if( sky > .25 ){
    float l = 10 - 4*sky; 
    GLfloat light_position[] = { 10000.0, 1.0, l, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  }

  	b.drawField();
  	b.drawRoad();
    b.drawTrees();

  glPushMatrix();
  glShadeModel(GL_SMOOTH);
  glTranslatef(15000, 500, -490);
  glRotatef(90, 0, 1, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(100,100,500);
  city.draw(0);
  glPopMatrix();

    glPushMatrix();
  glShadeModel(GL_SMOOTH);
  glTranslatef(20000, -5000, -440);
  glRotatef(90, 0, 1, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(100,100,500);
  city2.draw(0);
  glPopMatrix();

        glPushMatrix();
  glShadeModel(GL_SMOOTH);
  glTranslatef(-45000, -4800, -1090);
  glRotatef(90, 1, 0, 0);
  glScalef(500,250,180);
  city3.draw(0);
  glPopMatrix();

       glPushMatrix();
  glShadeModel(GL_SMOOTH);
  glTranslatef(4000, -2000, -890);
  glRotatef(90, 1, 0, 0);
  glScalef(500,300,100);
  city4.draw(0);
  glPopMatrix();



    glPushMatrix();
  glShadeModel(GL_SMOOTH);
  glTranslatef(30000, -3900 + sunM , 6000);
  glRotatef(90, 0, 1, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(7,7,7);
  sun.draw(1);
  glPopMatrix();


  glPushMatrix();
   glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);
  glTranslatef(body.moveX,0,5);
  glRotatef(90, 0, 1, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(.03,.03,.03);
  body.draw(0);
  glPopMatrix();


  if(wflag == 0){
 glPushMatrix();
   glShadeModel(GL_SMOOTH);
  glTranslatef(body.moveX,0,5);
  glRotatef(90, 0, 1, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(.03,.03,.03);
  backW.draw(0);
  glPopMatrix();
  }
  else{
  glPushMatrix();
  glShadeModel(GL_SMOOTH);
  glTranslatef(body.moveX,0,5);
  glRotatef(90, 0, 1, 0);
  glRotatef(90, 0, 0, 1);
  glScalef(.03,.03,.03);
  frontW.draw(0);
  glPopMatrix();
  }

	glutSwapBuffers();
}

void animate(int a){

  if(wflag == 0){
    wflag = 1;
  }
  else{
    wflag = 0;
  }
  if(sky< .1){
	body.moveX+=10;
  }
  else{
    body.moveX+=30;
  }
  sky+=.003;
  sunM+=20;
  wheelA+=1;
  if( wheelA > 360){
    wheelA=wheelA-360;
  }
	glutTimerFunc(100, animate, 0);
	glutPostRedisplay();
}

void keyboardListener(unsigned char key, int x,int y){

		
	if(key == 'q'){
	glutDestroyWindow(MainWindow);
	exit(1);
	}
}

void init(){
	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(70,	1,	0.1,	100000.0);

}


int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(LENGTH, WIDTH);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

	MainWindow = glutCreateWindow("Arman Kapbasov: ECS 175 Project 5");

	init();
	
	glEnable(GL_DEPTH_TEST);	

	glutDisplayFunc(display);

	glutTimerFunc(25, animate, 0);
	glutKeyboardFunc(keyboardListener); //in order to quit animation

  body.load("body.obj", NULL, true);
  backW.load("wheels.obj", NULL, true);
  frontW.load("wheels2.obj", NULL, true);
  city.load("hill.obj", NULL, true);
  sun.load("sun.obj", NULL, true);
  city2.load("hill.obj", NULL, true);
  city3.load("hill.obj", NULL, true);
  city4.load("hill.obj", NULL, true);


	glutMainLoop();	

	return 0;
}
