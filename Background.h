#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>


using namespace std;

class Background{
public:

	Background();
	void drawRoad();
	void drawField();
	void drawTrees();
	void GenericQuad(float r, float g, float b, int xx, int xy, int yx, int yy, int z);
};

#endif