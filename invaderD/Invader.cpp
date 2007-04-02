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
			imgB[i] = false;
			break;
		case 1:
			imgB[i] = true;
			atLeastThree++;
			break;
		default:
			imgB[i] = false;
			break;
		}
		imgU[i] = imgB[i];
	}

	for(int i = 15; i < 20; i++)
		imgU[i] = imgB[i-10];

	for(int i = 20; i < 25; i++)
		imgU[i] = imgB[i-20];
	
	// Make sure there are enough pixels in the invader image.
	if(atLeastThree < 3)
		generateImg();
}
void CInvader::generateInterPoints()
{
	p1.x = ( rand()%(WIDTH - (10*IPS)) ) + (5*IPS);
	p1.y = ( rand()%(HEIGHT - (PLAYERAREA*2) - (10*IPS)) ) + (5*IPS);
	pc.x = ( rand()%(WIDTH - (10*IPS)) ) + (5*IPS);
	pc.y = ( rand()%(HEIGHT - (PLAYERAREA*2) - (10*IPS)) ) + (5*IPS);
	p2.x = ( rand()%(WIDTH - (10*IPS)) ) + (5*IPS);
	p2.y = ( rand()%(HEIGHT - (PLAYERAREA*2) - (10*IPS)) ) + (5*IPS);

	// high in the x, small in the y
	/*p1.x = rand()%WIDTH;
	p1.y = rand()%(HEIGHT - (PLAYERAREA*2));
	pc.x = rand()%WIDTH;
	pc.y = rand()%(HEIGHT - (PLAYERAREA*2));
	p2.x = rand()%WIDTH;
	p2.y = rand()%(HEIGHT - (PLAYERAREA*2));*/
}
void CInvader::corruptImg()
{
	int r;
	for(int i = 0; i < 25; i++)
	{
		imgU[i] = 0;
	}
	for(int i = 0; i < 15; i++)
	{
		r = rand()%20;
		if(imgB[i] && r == 0)
		{
			imgB[i] = false;
		}
		if(!imgB[i] && r == 0)
		{
			imgB[i] = true;
		}
		imgU[i] = imgB[i];
	}
	if(getBlocks() < 3)
	{
		corruptImg();
		return;
	}
	for(int i = 15; i < 20; i++)
		imgU[i] = imgB[i-10];

	for(int i = 20; i < 25; i++)
		imgU[i] = imgB[i-20];
}
void CInvader::corruptInterPoints()
{
	double r;

	r = (rand()%(3*IPS*5))-(1.5*IPS*5);
	if( (r + p1.x) > (IPS*10) && (r + p1.x) < (WIDTH-(IPS*10)) )
		p1.x += r;
	r = (rand()%(3*IPS*5))-(1.5*IPS*5);
	if( (r + p1.y) > (IPS*10) && (r + p1.y) < ((HEIGHT - (PLAYERAREA*2))-(IPS*10)) )
		p1.y += r;

	r = (rand()%(3*IPS*5))-(1.5*IPS*5);
	if( (r + pc.x) > (IPS*10) && (r + pc.x) < (WIDTH-(IPS*10)) )
		pc.x += r;
	r = (rand()%(3*IPS*5))-(1.5*IPS*5);
	if( (r + pc.y) > (IPS*10) && (r + pc.y) < ((HEIGHT - (PLAYERAREA*2))-(IPS*10)) )
		pc.y += r;

	r = (rand()%(3*IPS*5))-(1.5*IPS*5);
	if( (r + p2.x) > (IPS*10) && (r + p2.x) < (WIDTH-(IPS*10)) )
		p2.x += r;
	r = (rand()%(3*IPS))-(1.5*IPS);
	if( (r + p2.y) > (IPS*10) && (r + p2.y) < ((HEIGHT - (PLAYERAREA*2))-(IPS*10)) )
		p2.y += r;
}
bool CInvader::getImgAtB(int p)
{
	if(p >= 0 && p < 15) 
		return imgB[p]; 
	else 
		return 0;
}
bool CInvader::getImgAtU(int p)
{
	if(p >= 0 && p < 25) 
		return imgU[p]; 
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
	sex = rand()%2;
	des_split = (double)(rand()%100);
	des_shoot = 100.0 - des_split;
	split_min = (rand()%100);
	shoot_min = rand()%50;
	splitMsg = false;
	followingMate = false;

	/*
	cout << sex << " sex\n";
	cout << des_split << " desire to split\n";
	cout << des_shoot << " desire to shoot\n";
	cout << split_min << " split min\n";
	cout << shoot_min << " shoot min\n";
	cout << "----------------------------------\n";
	*/
	pos = p1;
}
void CInvader::corrupt()
{
	//t = 0.0;
	corruptImg();
	corruptInterPoints();
	tFraction += ((rand()%10)-5)/10000.0f;
	//juice *= 2;
	des_split = fabs((double)(des_split + ((rand()%10)-5)));
	des_shoot = fabs((double)(des_shoot + ((rand()%10)-5)));
	split_min = fabs((double)(split_min + ((rand()%10)-5)));
	shoot_min = fabs((double)(shoot_min + ((rand()%10)-5)));
	splitMsg = false;
}
void CInvader::move()
{
	// qudratic intopolation
	if(t <= 0.0)
	{
		t = 0.0;
		/*if(followingMate)
		{
			p2 = posCloMate;
			pc.x+=(posCloMate.x - pc.x)/2;
			pc.y+=(posCloMate.y - pc.y)/2;
		}*/
		
	}
	if(t >= 1.0)
	{
		t = 1.0;
		/*if(followingMate)
		{
			p1 = posCloMate;
			pc.x+=(posCloMate.x - pc.x)/2;
			pc.y+=(posCloMate.y - pc.y)/2;
		}*/
	}
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
	else // would be better if went around in a circut ?
	{
		t -= tFraction;
		if(t < 0.0)
		{
			t = 0.0;
			forward = true;
			return;
		}
	}

	//use up juice when move
	juice -= tFraction/2;
}
void CInvader::action()
{
	double r = rand()%10000; // 10% change they will do something

	if(r <= des_split)
	{
		//split
		if(juice >= split_min && splitMsg == false && juice >= 1.0)
		{
			juice /= 2;
			splitMsg = true;
			//cout << juice << " after split\n";
		}
	}
	else if(r <= 100)
	{
		//shoot
		if(juice >= shoot_min && juice >= SHOOTCOST)
		{
			juice -= SHOOTCOST;
			CBomber::getInstance()->drop(pos);
			//cout << juice << " after shot\n";
		}
	}
}
bool CInvader::testHit(point2D p)
{
	for(int i = 0; i < 25; i++)
	{
		if( p.x >= (pos.x+((i/5)*IPS))-(IPS*2.5f) && p.x <= (pos.x+((i/5)*IPS))-(IPS*2.5f)+IPS &&
			p.y >= (pos.y+((i%5)*IPS))-(IPS*2.5f) && p.y <= (pos.y+((i%5)*IPS))-(IPS*2.5f)+IPS &&
			imgU[i] == true)
		/*if(p.x >= pos.x-(IPS*2.5f) && p.x <= pos.x+(IPS*2.5f) &&
			p.y >= pos.y-(IPS*2.5f) && p.y <= pos.y+(IPS*2.5f))*/
		{
			//imgU[i] = false;
			return true;
		}
	}
	return false;
}
int CInvader::getBlocks()
{
	int count = 0;
	for(int i = 0; i < 25; i++)
	{
		if(imgU[i])
			count++;
	}
	return count;
}
point2D CInvader::getIP(int p)
{
	switch(p)
	{
	case 0:
		return p1;
		break;
	case 1:
		return pc;
		break;
	case 2:
		return p2;
		break;
	}
}