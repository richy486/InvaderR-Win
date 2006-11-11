#include "Bomber.h"

CBomber::CBomber(void)
{
}

CBomber::~CBomber(void)
{
}
CBomber* CBomber::getInstance()
{
	static CBomber instance;
    return &instance;
}
point2D CBomber::getBombPos(int bomb)
{
	list<point2D>::iterator iter;
	point2D tp;
	int i = 0;
	for(iter=bombs.begin(); iter!=bombs.end(); iter++)
	{
		if(i == bomb)
		{
			tp.x = iter->x;
			tp.y = iter->y;
			return tp;
		}
		i++;
	}
	tp.x = 0.0;
	tp.y = 0.0;
	return tp;
}
void CBomber::drop(point2D p)
{
	point2D tp;
	tp.x = p.x;
	tp.y = p.y;
	bombs.push_back(tp);
}
void CBomber::progress()
{
	point2D tp;
	list<point2D>::iterator iter;
	
	for(int i = 0; i < 1; i++)
	{
		iter=bombs.begin(); 
		while(iter!=bombs.end())
		{
			tp.x = iter->x;
			tp.y = iter->y;
			// check for collisions with base
			/*if(iter->y <=50+(5*IPS))
			{
				if(CBaseSet::getInstance()->checkHits(tp))
				{
					iter = bombs.erase(iter);
				}
			}*/

			// check for collisions with player
			if(iter->y >= HEIGHT-PLAYERAREA && CPlayer::getInstance()->testHit(tp))
			{
				iter = bombs.erase(iter);
			}

			// check if off screen
			else if(iter->y >= HEIGHT)
			{
				iter = bombs.erase(iter);
			}
			else
			{
				iter->y +=1;
				iter++; 
			}
			
		}
	}
}
void CBomber::clearBombs()
{
	bombs.clear();
}