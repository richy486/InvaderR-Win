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

#include ".\invader.h"

CInvader::CInvader(void)
{
}

CInvader::~CInvader(void)
{
}
// Generate the image of the invader.
void CInvader::generateInvader()
{
	int atLeastThree = 0;
	for(int i = 0; i < 15; i++)
	{
		img[i] = rand()%2;

		if(img[i] == true)
			atLeastThree++;
	}
	
	// Make sure there are enough pixels in the invader image.
	if(atLeastThree < 3)
		generateInvader();
}
// Draws the invader at its position.
void CInvader::draw()
{
	// colour based on height.
	glColor3f(1-(p_pos.y/1000)*2, 1-(p_pos.y/1000)*2, 1-(p_pos.y/1000)*2);
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