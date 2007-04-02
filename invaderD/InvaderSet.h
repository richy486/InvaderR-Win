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

#ifndef _INVADERSET_H_
#define _INVADERSET_H_

#include <list>
#include <math.h>
#include "common.h"
#include "Invader.h"

class CInvaderSet
{
protected:
	std::list<CInvader> lInvaders;
public:
	CInvaderSet(void);
	~CInvaderSet(void);
	static CInvaderSet* getInstance();

	int getNumInvaders(){return lInvaders.size();}

	void createBasicInvaders(int amount);
	void moveInvaders();
	void actionInvaders();
	bool testNoJuice();
	bool getInvaderImgAtWM(int invader, int pt);
	bool getInvaderSex(int invader);
	point2D getInvaderPos(int invader);
	bool testHits(point2D p);
	void clearInvaders();
	void corruptAll();
	void findClosestMates();

	point2D getInvaderLIP(int invader, int p);
	
};

#endif
