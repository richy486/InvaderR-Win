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

#pragma once

#include <stdlib.h>
#include <time.h>
#include <list>
using namespace std;
#include ".\invader.h"
#include ".\bomber.h"


class CInvaderSet
{
protected:
	list<CInvader> I_set;
	int side2side;
	bool side; //true = left, false = right
	bool playing;
	bool outcome;
public:
	CInvaderSet(void);
	~CInvaderSet(void);
	static CInvaderSet* getInstance();

	void setPlaying(bool val){playing = val;}
	bool getPlaying(){return playing;}
	void setOutcome(bool val){outcome = val;}
	bool getOutcome(){return outcome;}

	int getNumInvaders(){return (int)I_set.size();}
	void spawnNewSet();
	bool testHits(Point p);
	void move(float seconds);
	void restart();
	void killAll();

	void drawSet();
};
