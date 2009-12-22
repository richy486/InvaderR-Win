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
	Shot shot;
	shot.m_isDead = false;

	shot.m_position.x = p.x +(2.5f*IPS);
	shot.m_position.y = p.y;
	m_shots.push_back(shot);
}
// Move a bomb down the screen, if it is in range check if a bomb will hit a base or the player.
void CBomber::progress(float seconds)
{
	Point t_p;
	list<Shot>::iterator iter;

#if 1 //RA - testing
	//for(int i = 0; i < 5; i++) // ???????
	{
		iter = m_shots.begin(); 
		while(iter != m_shots.end())
		{
			t_p.x = iter->m_position.x;
			t_p.y = iter->m_position.y;
			if(iter->m_position.y <= 50 + (5 * IPS))
			{
				if(iter->m_position.y <= 0 || CBaseSet::getInstance()->checkHits(t_p))
				{
					//iter = m_shots.erase(iter);
					iter->m_isDead = true;
				}
			}

			if(iter->m_position.y <= 50 + (5 * IPS) && CPlayer::getInstance()->testHit(t_p))
			{
				//iter = m_shots.erase(iter);
				iter->m_isDead = true;
				CInvaderSet::getInstance()->setPlaying(false);
				CInvaderSet::getInstance()->setOutcome(false);
			}
			else
			{
				iter->m_position.y -= 100.0f * seconds;
				//iter++; 
			}
			iter++;
		}
	}

	iter = m_shots.begin(); 
	while(iter != m_shots.end())
	{
		if (iter->m_isDead)
		{
			iter = m_shots.erase(iter);
		}
		else
		{
			iter++;
		}
	}
#endif
}
// Kill all the bombs.
void CBomber::killAll()
{
	m_shots.clear();
}
// Draw the bombs.
void CBomber::draw()
{
	glColor3f(1.0, 0.0, 0.0);
	list<Shot>::iterator iter;
	for(iter = m_shots.begin(); iter != m_shots.end(); ++iter)
	{
		glBegin(GL_POLYGON);
			glVertex3f(iter->m_position.x,		(iter->m_position.y), 0.0f);
			glVertex3f(iter->m_position.x+IPS,	(iter->m_position.y), 0.0f);
			glVertex3f(iter->m_position.x+IPS,	(iter->m_position.y)+IPS, 0.0f);
			glVertex3f(iter->m_position.x,		(iter->m_position.y)+IPS, 0.0f);
			glVertex3f(iter->m_position.x,		(iter->m_position.y), 0.0f);
		glEnd();
	}
}