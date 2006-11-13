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
#include "bomber.h"


class CInvader
{
protected:
	point2D p1, pc, p2;	// points to intopolate through
	point2D pos;		// position
	double tFraction;	// fraction of t for intopolation (0.005);
	bool imgB[15];		// base image of invader, to be mirriored
	bool imgU[30];		// usable image of invader to be deformed
	double t;			// position in intopolation 0 <= t <= 1
	bool forward;		// is invader being intopolated forward or backwards

	double juice;		// how much energy/fule/juice the invader has to use
	bool sex;			// the sex of the invader
	double shoot_min;	// will not shoot if have lower than this value in juice
	double split_min;	// will not split if have lower than this value in juice
	double des_split;	// desire to split
	double des_shoot;	// desire to shoot
	bool splitMsg;		// true if invader wants to split
	int breedMsg;		// 0 if not breeding, 1 if breeding, 2 if have recently breeded.
	point2D posCloMate;	// the position of closest mate.
	bool followingMate;// if a mate ahs been found to move towards;
	
	void generateImg();
	void generateInterPoints();

	void corruptImg();
	void corruptInterPoints();

public:
	CInvader(void);
	~CInvader(void);

	point2D getPos(){return pos;}
	bool getSplitMsg(){return splitMsg;}
	void aceptSplitMsg(){splitMsg = false;}
	point2D getPointOne(){return p1;}
	void addJuice(double j){juice += j;}
	double getJuice(){return juice;}
	int getBreedMsg(){return breedMsg;}
	void setBreedMsg(int b){if(b==NOT||b==AM||b==DID) breedMsg = b;}
	bool getSex(){return sex;}
	void setCloMate(point2D p, bool l){posCloMate = p; followingMate = l;}
	
	bool getImgAtB(int p);	// get the actual array values
	bool getImgAtU(int p);	// get the full image by including mirrored values

	void generateBasic();
	void corrupt();
	void parentAtributes();

	void move();
	void action();
	bool testHit(point2D p);
		
	int getBlocks();
	point2D getIP(int p);
};

#endif
