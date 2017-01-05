#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "Car.h"

#define WIDTH 800
#define LENGTH 800


Car::Car(){
	moveX= 0;
	moveY=0;
	centerX=0;
	centerY=0;

}
void Car::setCenter(int x, int y, int z){
	centerZ = z;
	centerY = y;
	centerX = x;
}
void Car::load(const char* filename, const char* basepath, bool triangulate){
  		std::cout << "Loading " << filename << std::endl;


  		std::string err;
  		bool ret = tinyobj::LoadObj(shapes, materials, err, filename, basepath, triangulate);

  		if (!err.empty()) {
    		std::cerr << err << std::endl;
  		}

  		if (!ret) {
    		printf("Failed to load/parse .obj.\n");
    		return;
  		}

}	

void Car::draw(int f){
	for (size_t i = 0; i < shapes.size(); i++) {
	    glBegin(GL_TRIANGLES);
	    for(size_t v = 0; v < shapes[i].mesh.indices.size() / 3; v++) {

	  //  glDisable(GL_COLOR_MATERIAL);

	      glEnable(GL_TEXTURE_2D);
	      glBindTexture(GL_TEXTURE_2D, 0);
	      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	      GLfloat* ambient = (materials[shapes[i].mesh.material_ids[v]]).ambient;
	      GLfloat* diffuse = (materials[shapes[i].mesh.material_ids[v]]).diffuse;
	      GLfloat* specular = (materials[shapes[i].mesh.material_ids[v]]).specular;
	      glColor3f(diffuse[0], diffuse[1], diffuse[2]);
	     // GLfloat* shininess;
	    //  shininess[0] = (materials[shapes[i].mesh.material_ids[v]]).shininess;
	      if(f == 1){
	      	GLfloat glow[] = {1, 1, 0.0};
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glow);
	      }
	    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	   // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	        int i1=shapes[i].mesh.indices[3*v+0],
	        i2=shapes[i].mesh.indices[3*v+1],
	        i3=shapes[i].mesh.indices[3*v+2];
	        //cout<<"NORMALS: "<<shapes[i].mesh.normals[3*i1+0] <<" | "<< shapes[i].mesh.normals[3*i1+1]<<" | "<<  shapes[i].mesh.normals[3*i1+2]<<endl;
	      //cout<<"shapes[i].mesh.positions[3*i1+0]"<<shapes[i].mesh.positions[3*i1+0]<<endl;
	     // cout<<"shapes[i].mesh.texcoords[2*i1+0]"<<shapes[i].mesh.texcoords[2*i1+0] <<"shapes[i].mesh.texcoords[2*i1+1]"<<shapes[i].mesh.texcoords[2*i1+1] <<endl;
	     // cout<<endl;
	      glTexCoord2f(shapes[i].mesh.texcoords[2*i1+0],shapes[i].mesh.texcoords[2*i1+1]);
	      glNormal3f( shapes[i].mesh.normals[3*i1+0], shapes[i].mesh.normals[3*i1+1], shapes[i].mesh.normals[3*i1+2]);
	      glVertex3d(
	      shapes[i].mesh.positions[3*i1+0],
	      shapes[i].mesh.positions[3*i1+1],
	      shapes[i].mesh.positions[3*i1+2]);
	      glTexCoord2f(shapes[i].mesh.texcoords[2*i2+0],shapes[i].mesh.texcoords[2*i2+1]);
	      glNormal3f( shapes[i].mesh.normals[3*i2+0], shapes[i].mesh.normals[3*i2+1], shapes[i].mesh.normals[3*i2+2]);
	      glVertex3d(
	      shapes[i].mesh.positions[3*i2+0],
	      shapes[i].mesh.positions[3*i2+1],
	      shapes[i].mesh.positions[3*i2+2]);
	      glTexCoord2f(shapes[i].mesh.texcoords[2*i3+0],shapes[i].mesh.texcoords[2*i3+1]);
	      glNormal3f( shapes[i].mesh.normals[3*i3+0], shapes[i].mesh.normals[3*i3+1], shapes[i].mesh.normals[3*i3+2]);
	      glVertex3d(
	      shapes[i].mesh.positions[3*i3+0],
	      shapes[i].mesh.positions[3*i3+1],
	      shapes[i].mesh.positions[3*i3+2]);
	    }
	    glEnd();
	}
}