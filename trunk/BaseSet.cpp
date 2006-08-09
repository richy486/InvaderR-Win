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

#include ".\baseset.h"

CBaseSet::CBaseSet(void)
{

}
CBaseSet::~CBaseSet(void)
{
}
CBaseSet* CBaseSet::getInstance()
{
	static CBaseSet instance;
    return &instance;
}
// Generate and place 5 bases.
void CBaseSet::makeBases()
{
	Point t_p;
	for(int i = 0; i < 5; i++)
	{
		base[i].generate();
		t_p.x = i*100+30;
		t_p.y = 50;
		base[i].setPos(t_p);
	}
}
// Check hits for all the bases.
bool CBaseSet::checkHits(Point p)
{
	for(int i = 0; i < 5; i++)
	{
		if(base[i].testHit(p))
			return true;
	}
	return false;
}
// Draw all the bases.
void CBaseSet::drawBases()
{
	for(int i = 0; i < 5; i++)
	{
		base[i].drawBase();
	}
}