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

#include ".\text.h"

CText::CText(void)
{
	x = 115;
	y = 60;
}

CText::~CText(void)
{
}
CText* CText::getInstance()
{
	static CText instance;
    return &instance;
}
// Set the image to nothing
void CText::displayNothing()
{
	for(int i = 0; i < 15; i++)
	{
		img[i] = false;
	}
}
// Set the image to :)
void CText::displayWin()
{
	for(int i = 0; i < 15; i++)
	{
		img[i] = false;
	}
	img[1] = true;
	img[5] = true;
	img[8] = true;
	img[10] = true;

}
// Set the image to :(
void CText::displayLoose()
{
	for(int i = 0; i < 15; i++)
	{
		img[i] = false;
	}
	img[0] = true;
	img[6] = true;
	img[8] = true;
	img[11] = true;
}
// Draw the image.
void CText::draw()
{
	glColor3f(1.0, 1.0, 1.0);
	for(int i = 0; i < 15; i++)
	{
		if(img[i] == true)
		{
			
			glBegin(GL_POLYGON);
				glVertex3f(x+((i/5)*TPS),		(y)+((i%5)*TPS), 0.0f);
				glVertex3f(x+((i/5)*TPS)+TPS,	(y)+((i%5)*TPS), 0.0f);
				glVertex3f(x+((i/5)*TPS)+TPS,	(y)+((i%5)*TPS)+TPS, 0.0f);
				glVertex3f(x+((i/5)*TPS),		(y)+((i%5)*TPS)+TPS, 0.0f);
				glVertex3f(x+((i/5)*TPS),		(y)+((i%5)*TPS), 0.0f);
			glEnd();

			if(i < 5)
			{
				glBegin(GL_POLYGON);
					glVertex3f(x+((i/5)*TPS)+(4*TPS),		(y)+((i%5)*TPS), 0.0f);
					glVertex3f(x+((i/5)*TPS)+TPS+(4*TPS),	(y)+((i%5)*TPS), 0.0f);
					glVertex3f(x+((i/5)*TPS)+TPS+(4*TPS),	(y)+((i%5)*TPS)+TPS, 0.0f);
					glVertex3f(x+((i/5)*TPS)+(4*TPS),		(y)+((i%5)*TPS)+TPS, 0.0f);
					glVertex3f(x+((i/5)*TPS)+(4*TPS),		(y)+((i%5)*TPS), 0.0f);
				glEnd();
			}
			if(i >= 5 && i < 10)
			{
				glBegin(GL_POLYGON);
					glVertex3f(x+((i/5)*TPS)+(2*TPS),		(y)+((i%5)*TPS), 0.0f);
					glVertex3f(x+((i/5)*TPS)+TPS+(2*TPS),	(y)+((i%5)*TPS), 0.0f);
					glVertex3f(x+((i/5)*TPS)+TPS+(2*TPS),	(y)+((i%5)*TPS)+TPS, 0.0f);
					glVertex3f(x+((i/5)*TPS)+(2*TPS),		(y)+((i%5)*TPS)+TPS, 0.0f);
					glVertex3f(x+((i/5)*TPS)+(2*TPS),		(y)+((i%5)*TPS), 0.0f);
				glEnd();
			}//*/
		}
	}

	
}