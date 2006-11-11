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

#include "Invader.h"

CInvader::CInvader(void)
{
}

CInvader::~CInvader(void)
{
}

void CInvader::generateImg()
{
	int atLeastThree = 0;
	for(int i = 0; i < 15; i++)
	{
		switch(rand()%2)
		{
		case 0:
			img[i] = false;
			break;
		case 1:
			img[i] = true;
			atLeastThree++;
			break;
		default:
			img[i] = false;
			break;
		}
	}
	
	// Make sure there are enough pixels in the invader image.
	if(atLeastThree < 3)
		generateImg();
}
void CInvader::generateInterPoints()
{
	p1.x = rand()%(WIDTH - 5) + 5;
	p1.y = rand()%(HEIGHT - PLAYERAREA*2) + 5;
	pc.x = rand()%(WIDTH - 5) + 5;
	pc.y = rand()%(HEIGHT) + 5;
	p2.x = rand()%(WIDTH - 5) + 5;
	p2.y = rand()%(HEIGHT - PLAYERAREA*2) + 5;
}
bool CInvader::getImgAt(int p)
{
	if(p >= 0 && p <= 15) 
		return img[p]; 
	else 
		return 0;
}
bool CInvader::getImgAtWM(int p)
{
	if(p >= 0 && p < 15) 
		return img[p]; 
	else if(p >= 15 && p < 20)
		return img[p-10];
	else if(p >= 20 && p < 25)
		return img[p-20];
	else 
		return 0;
}
void CInvader::generateBasic()
{
	t = 0.0;
	generateImg();
	generateInterPoints();
	tFraction = (rand()%100)/10000.0f;
	juice = (double)100.0;
	des_split = (double)(rand()%100);
	des_shoot = 100.0 - des_split;
	
	pos = p1;
}
void CInvader::move()
{
	// qudratic intopolation
	pos.x = p1.x*pow((1-t),2) + 2*t*(1-t)*pc.x + p2.x*pow(t,2);
	pos.y = p1.y*pow((1-t),2) + 2*t*(1-t)*pc.y + p2.y*pow(t,2);
	if(forward)
	{
		t += tFraction;
		if(t > 1.0)
		{
			t = 1.0;
			forward = false;
			return;
		}
	}
	else // would be better if went around in a circut !
	{
		t -= tFraction;
		if(t < 0.0)
		{
			t = 0.0;
			forward = true;
			return;
		}
	}
}
void CInvader::action()
{
	if(rand()%100 <= des_split)
	{
		//split
	}
	else
	{
		//shoot
	}
}