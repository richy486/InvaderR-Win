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

#include "Shooter.h"

CShooter::CShooter(void)
{
}

CShooter::~CShooter(void)
{
}
CShooter* CShooter::getInstance()
{
	static CShooter instance;
    return &instance;
}
point2D CShooter::getShotPos(int shot)
{
	list<point2D>::iterator iter;
	point2D tp;
	int i = 0;
	for(iter=shots.begin(); iter!=shots.end(); iter++)
	{
		if(i == shot)
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
void CShooter::shoot(point2D p)
{
	point2D tp;
	tp.x = p.x;
	tp.y = p.y;
	shots.push_back(tp);
}
void CShooter::progress()
{
	point2D tp;
	list<point2D>::iterator iter;
	
	for(int i = 0; i < 5; i++)
	{
		iter=shots.begin(); 
		while(iter!=shots.end())
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

			// check for collisions with invaders
			/*if(CInvaderSet::getInstance()->testHits(tp))
			{
				iter = shots.erase(iter);
			}*/

			// check if off screen
			if(iter->y <= 0)
			{
				iter = shots.erase(iter);
			}
			else
			{
				iter->y -=1;
				iter++; 
			}
			
		}
	}
}
void CShooter::destroyShot(int s)
{
	list<point2D>::iterator iter;
	int i = 0;
	for(iter=shots.begin(); iter!=shots.end(); iter++)
	{
		if(i == s)
		{
			iter = shots.erase(iter);
			return;
		}
		i++;
	}
}
void CShooter::clearShots()
{
	shots.clear();
}