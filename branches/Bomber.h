#ifndef _BOMBER_H_
#define _BOMBER_H_

#include <list>
#include "common.h"
#include "player.h"

class CBomber
{
protected:
	list<point2D> bombs;
public:
	CBomber(void);
	~CBomber(void);
	static CBomber* getInstance();

	int getNumBombs(){return bombs.size();}

	point2D getBombPos(int bomb);

	void drop(point2D p);
	void progress();
};

#endif