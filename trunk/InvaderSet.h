#pragma once

#include <list>
using namespace std;
#include ".\invader.h"

class CInvaderSet
{
protected:
	list<CInvader> I_set;
	int side2side;
	bool side; //true = left, false = right
public:
	CInvaderSet(void);
	~CInvaderSet(void);
	static CInvaderSet* getInstance();

	int getNumInvaders(){return I_set.size();}
	void spawnNewSet();
	bool testHits(Point p);
	void move();

	void drawSet();

};
