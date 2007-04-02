/* invaderR, space invaders clone
 * Copyright (C) 2006 Richard Adem richy486@gmail.com
 *
 * invaderR is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * invaderR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
	std::list<point2D>::iterator iter;
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
	
	tp.x = 0.0f;
	tp.y = 0.0f;
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
	std::list<point2D>::iterator iter;
	
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
			if(iter->y >= HEIGHT-PLAYERAREA && CPlayer::getInstance()->testHit(tp) && !CEnd::getInstance()->getEnd())
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