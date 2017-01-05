#ifndef CAR_H
#define CAR_H

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "tiny_obj_loader.h"

using namespace std;

class Car{
public:
		int moveX;
		int moveY;
		int centerX;
		int centerY;
		int centerZ;
		int count;

 	 std::vector<tinyobj::shape_t> shapes;
  	 std::vector<tinyobj::material_t> materials;

	Car();
	void setCenter(int x, int y, int z);
	void load(const char* filename, const char* basepath, bool triangulate);
	void draw(int f);
};

#endif