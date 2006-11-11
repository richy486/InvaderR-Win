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

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "common.h"
#include "shooter.h"

class CPlayer
{
protected:
	point2D pos;
	bool img[25];
	double gXMov;
	bool rShoot;
public:
	CPlayer(void);
	~CPlayer(void);
	static CPlayer* getInstance();

	point2D getPos(){return pos;}
	void setPos(point2D p){pos = p;}
	void posPlusMove(){pos.x += gXMov;}
	void posMinusMove(){pos.x -= gXMov;}
	double getMove(){return gXMov;}
	void setMove(double m){gXMov = m;}
	void addMove(double m){gXMov += m;}
	void subMove(double m){gXMov -= m;}
	void slowdown(){gXMov *= SLOWDOWN;};

	void start();
	void makeImg();

	bool getImgAt(int p);	// get the actual array values

	bool testHit(point2D p);
	void shoot();
	void readyShoot(){rShoot = true;}

	int getBlocks();
};

#endif
