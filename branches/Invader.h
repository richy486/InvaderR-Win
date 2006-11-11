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

#ifndef _INVADER_H_
#define _INVADER_H_

#include <math.h>
#include "common.h"


class CInvader
{
protected:
	point2D p1, pc, p2;	// points to intopolate through
	point2D pos;		// position
	double tFraction;	// fraction of t for intopolation (0.005);
	bool img[15];		// image of invader, to be mirriored
	double t;			// position in intopolation 0 <= t <= 1
	bool forward;		// is invader being intopolated forward or backwards

	double juice;		// how much energy/fule/juice the invader has to use
	double des_split;	// desire to split
	double des_shoot;	// desire to shoot
	
	void generateImg();
	void generateInterPoints();

public:
	CInvader(void);
	~CInvader(void);

	point2D getPos(){return pos;}
	
	bool getImgAt(int p);	// get the actual array values
	bool getImgAtWM(int p);	// get the full image by including mirrored values

	void generateBasic();

	void move();
	void action();
	
};

#endif
