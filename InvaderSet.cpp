#include ".\invaderset.h"

CInvaderSet::CInvaderSet(void)
{
	side = true;
	side2side = 0;
}

CInvaderSet::~CInvaderSet(void)
{
}
CInvaderSet* CInvaderSet::getInstance()
{
	static CInvaderSet instance;
    return &instance;
}
void CInvaderSet::spawnNewSet()
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			CInvader t_inv;
			t_inv.generateInvader();
			Point t_pnt;
			t_pnt.x = j*30+170;
			t_pnt.y = i*30+180;
			t_inv.setPos(t_pnt);
			I_set.push_back(t_inv);
		}
	}
}
bool CInvaderSet::testHits(Point p)
{
	list<CInvader>::iterator iter;

	iter=I_set.begin(); 
	while(iter!=I_set.end())
	{
		if(p.x >= iter->getPos().x && p.x <= iter->getPos().x+(IPS*5) && 
			p.y >= iter->getPos().y && p.y <= iter->getPos().y+(IPS*5))
		{
			iter = I_set.erase(iter);
			return true;
		}
		else
		{
			iter++; 
		}
		
	}
	return false;
}
void CInvaderSet::move()
{
	if(I_set.empty())
	{
		spawnNewSet();
		side2side = 0;
		side = true;
	}
	Point t_p;
	list<CInvader>::iterator iter;
	int x,y;
	
	if(side == true)
	{
		side2side++;
		x = - 2;
		if(side2side >= 75)
		{
			side2side = 0;
			side = false;
			y = -2;
		}
		else
		{
			y = 0;
		}
		
	}
	else
	{
		side2side++;
		x = 2;
		if(side2side >= 75)
		{
			side2side = 0;
			side = true;
			y = -2;
		}
		else
		{
			y = 0;
		}
	}
	for(iter=I_set.begin(); iter!=I_set.end(); ++iter)
	{
		t_p.x = iter->getPos().x + x;
		t_p.y = iter->getPos().y + y;
		iter->setPos(t_p);
	}

}
void CInvaderSet::drawSet()
{
	list<CInvader>::iterator iter;
	for(iter=I_set.begin(); iter!=I_set.end(); ++iter)
	{
		iter->draw();
	}
}