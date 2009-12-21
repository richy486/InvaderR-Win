#pragma once

//#include <GL/glut.h>
#include <math.h>
#include ".\consts.h"

class CBase
{
protected:
	Point p_pos;
	bool img[25];
public:
	CBase(void);
	~CBase(void);

	void setPos(Point p){p_pos = p;}
	Point getPos(){return p_pos;}

	void generate();
	bool testHit(Point p);

	void drawBase();
};
