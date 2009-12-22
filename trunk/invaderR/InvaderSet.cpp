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
// Fill up the list with 50 invaders.
void CInvaderSet::spawnNewSet()
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			CInvader t_inv;
			t_inv.generateInvader();
			Point t_pnt;
			t_pnt.x = j * 30.0f + 160.0f;
			t_pnt.y = i * 30.0f + 180.0f;
			t_inv.setPos(t_pnt);
			I_set.push_back(t_inv);
		}
	}
}
// Test if a players shot has hit an invader.
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
// Move the invaders adding slop,
// Also has the invaders shoot
// The less invaders the larger the change they will shoot.
void CInvaderSet::move(float seconds)
{
	if(I_set.empty())
	{
		playing = false;
		outcome = true;
	}
	Point t_p;
	list<CInvader>::iterator iter;
	float x; // ,y;
	
	if (side == true)
	{
		side2side++;
		x = -1;
		if(side2side >= 75)
		{
			side2side = 0;
			side = false;
		}
	}
	else
	{
		side2side++;
		x = 1;
		if(side2side >= 75)
		{
			side2side = 0;
			side = true;
		}
	}

	for(iter=I_set.begin(); iter!=I_set.end(); ++iter)
	{
		t_p.x = iter->getPos().x + x*((float)((rand()%5)+15)/10);
		if(t_p.x > 460)
			t_p.x -= ((float)((rand()%10)+10)/10) * seconds * 100.0f;
		if(t_p.x < 20)
			t_p.x += ((float)((rand()%10)+10)/10) * seconds * 100.0f;
		t_p.y = iter->getPos().y - (((float)(rand()%20)/100) * seconds * 25.0f);
		iter->setPos(t_p);
		
		if(iter->getPos().y <= 0)
		{
			playing = false;
			outcome = false;
		}

		if(rand()%(I_set.size()*20) == 1)
		{
			CBomber::getInstance()->shoot(t_p);
		}
	}

}
// Start a new game.
void CInvaderSet::restart()
{
	killAll();
	spawnNewSet();
	side2side = 0;
	side = true;
}
// Kill all the invaders.
void CInvaderSet::killAll()
{
	I_set.clear();
}
// Call the drawing function for all the invaders.
void CInvaderSet::drawSet()
{
	list<CInvader>::iterator iter;
	for(iter=I_set.begin(); iter!=I_set.end(); ++iter)
	{
		iter->draw();
	}
}