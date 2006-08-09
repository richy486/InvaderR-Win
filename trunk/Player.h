#pragma once

#include <GL/glut.h>
#include "consts.h"

class CPlayer
{
protected:
	Point p_pos;
public:
	CPlayer(void);
	~CPlayer(void);

	void setPos(Point p){p_pos = p;}
	Point getPos(){return p_pos;}

	void start();
	void draw();

};
