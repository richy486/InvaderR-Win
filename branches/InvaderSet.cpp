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

#include "InvaderSet.h"

CInvaderSet::CInvaderSet(void)
{
}

CInvaderSet::~CInvaderSet(void)
{
}
CInvaderSet* CInvaderSet::getInstance()
{
	static CInvaderSet instance;
    return &instance;
}
void CInvaderSet::createBasicInvaders(int amount)
{
	for(int i = 0; i < amount; i++)
	{
		CInvader iTemp;// = new CInvader;
		iTemp.generateBasic();
		lInvaders.push_back(iTemp);
		//delete iTemp;
	}
}
void CInvaderSet::moveInvaders()
{
	list<CInvader>::iterator iter;
	for(iter=lInvaders.begin(); iter!=lInvaders.end(); iter++)
	{
		iter->move();
	}
}
bool CInvaderSet::getInvaderImgAtWM(int invader, int pt)
{
	list<CInvader>::iterator iter;
	int i = 0;
	for(iter=lInvaders.begin(); iter!=lInvaders.end(); iter++)
	{
		if(i == invader)
			return iter->getImgAtWM(pt);
		
		i++;
	}
	return 0;
}
point2D CInvaderSet::getInvaderPos(int invader)
{
	list<CInvader>::iterator iter;
	int i = 0;
	for(iter=lInvaders.begin(); iter!=lInvaders.end(); iter++)
	{
		if(i == invader)
		{
			return iter->getPos();
		}
		
		i++;
	}
	point2D tp;
	tp.x = 0.0;
	tp.y = 0.0;
	return tp;
}