#pragma once

#include <GL/glut.h>
#include <list>
using namespace std;
#include ".\invaderset.h"
#include "consts.h"

class CShooter
{
protected:
	list<Point> shots;
public:
	CShooter(void);
	~CShooter(void);

	void shoot(Point p);
	void progress();
	void draw();
};
