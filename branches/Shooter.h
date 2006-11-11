#ifndef _SHOOTER_H_
#define _SHOOTER_H_

#include <list>
#include "common.h"
//#include "invaderset.h"

class CShooter
{
protected:
	list<point2D> shots;
public:
	CShooter(void);
	~CShooter(void);
	static CShooter* getInstance();

	int getNumShots(){return shots.size();}

	point2D getShotPos(int shot);

	void shoot(point2D p);
	void progress();
	void destroyShot(int s);
};

#endif
