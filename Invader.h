#pragma once

#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include "consts.h"

class CInvader
{
protected:
	Point p_pos;
	bool img[15];
public:
	CInvader(void);
	~CInvader(void);

	void setPos(Point p){p_pos = p;}
	Point getPos(){return p_pos;}

	void generateInvader();
	void remakeInvader();
	
	
	void draw();
};
