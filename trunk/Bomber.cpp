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

#include ".\bomber.h"

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
// Shoot a bomb.
void CBomber::shoot(Point p)
{
	Point t_p;
	t_p.x = p.x +(2.5*IPS);
	t_p.y = p.y;
	shots.push_back(t_p);
}
// Move a bomb down the screen.
void CBomber::progress()
{
	list<Point>::iterator iter;

	iter=shots.begin(); 
	while(iter!=shots.end())
	{
		Point t_p;
		t_p.x = iter->x;
		t_p.y = iter->y;
		if(iter->y <= 0)
		{
			iter = shots.erase(iter);
		}
		if(CPlayer::getInstance()->testHit(t_p))
		{
			iter = shots.erase(iter);
			CInvaderSet::getInstance()->setPlaying(false);
			CInvaderSet::getInstance()->setOutcome(false);
		}
		else
		{
			iter->y -=5;
			iter++; 
		}
		
	}
}
// Kill all the bombs.
void CBomber::killAll()
{
	shots.clear();
}
// Draw the bombs.
void CBomber::draw()
{
	glColor3f(1.0, 0.0, 0.0);
	list<Point>::iterator iter;
	for(iter=shots.begin(); iter!=shots.end(); ++iter)
	{
		
			glBegin(GL_POLYGON);
				glVertex2i(iter->x,		(iter->y));
				glVertex2i(iter->x+IPS,	(iter->y));
				glVertex2i(iter->x+IPS,	(iter->y)+IPS);
				glVertex2i(iter->x,		(iter->y)+IPS);
				glVertex2i(iter->x,		(iter->y));
			glEnd();
	}
}