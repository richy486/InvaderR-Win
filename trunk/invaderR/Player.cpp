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

#include ".\player.h"

// Set the image of the player.
CPlayer::CPlayer(void)
{
	for(int i = 0; i < 15; i++)
	{
		img[i] = false;
	}
	img[0] = true;
	img[1] = true;
	img[6] = true;
	img[7] = true;
	img[8] = true;
	img[11] = true;
	img[12] = true;
	img[13] = true;
	img[14] = true;
}

CPlayer::~CPlayer(void)
{
}
CPlayer* CPlayer::getInstance()
{
	static CPlayer instance;
    return &instance;
}
// Put the player in the start position.
void CPlayer::start()
{
	p_pos.x = 230;
	p_pos.y = 10;
}
// Test if the player was hit by an invader's bomb.
bool CPlayer::testHit(Point p)
{
	if(p.x >= p_pos.x-1 && p.x <= p_pos.x+(IPS*5)-1 && 
			p.y >= p_pos.y && p.y <= p_pos.y+(IPS*5))
			return true;
	else
	return false;
}
// Draw the player at its position.
void CPlayer::draw()
{
	glColor3f(1.0, 1.0, 1.0);
	for(int i = 0; i < 15; i++)
	{
		if(img[i] == true)
		{
			
			glBegin(GL_POLYGON);
				glVertex3f(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS), 0.0f);
				glVertex3f(p_pos.x+((i/5)*IPS)+IPS,	(p_pos.y)+((i%5)*IPS), 0.0f);
				glVertex3f(p_pos.x+((i/5)*IPS)+IPS,	(p_pos.y)+((i%5)*IPS)+IPS, 0.0f);
				glVertex3f(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS)+IPS, 0.0f);
				glVertex3f(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS), 0.0f);
			glEnd();

			if(i < 5)
			{
				glBegin(GL_POLYGON);
					glVertex3f(p_pos.x+((i/5)*IPS)+(4*IPS),		(p_pos.y)+((i%5)*IPS), 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+IPS+(4*IPS),	(p_pos.y)+((i%5)*IPS), 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+IPS+(4*IPS),	(p_pos.y)+((i%5)*IPS)+IPS, 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+(4*IPS),		(p_pos.y)+((i%5)*IPS)+IPS, 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+(4*IPS),		(p_pos.y)+((i%5)*IPS), 0.0f);
				glEnd();
			}
			if(i >= 5 && i < 10)
			{
				glBegin(GL_POLYGON);
					glVertex3f(p_pos.x+((i/5)*IPS)+(2*IPS),		(p_pos.y)+((i%5)*IPS), 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+IPS+(2*IPS),	(p_pos.y)+((i%5)*IPS), 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+IPS+(2*IPS),	(p_pos.y)+((i%5)*IPS)+IPS, 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+(2*IPS),		(p_pos.y)+((i%5)*IPS)+IPS, 0.0f);
					glVertex3f(p_pos.x+((i/5)*IPS)+(2*IPS),		(p_pos.y)+((i%5)*IPS), 0.0f);
				glEnd();
			}
		}
	}
}