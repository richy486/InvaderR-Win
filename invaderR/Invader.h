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

#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include ".\consts.h"

class CInvader
{
protected:
	Point p_pos;
	bool img[15];
public:
	CInvader(void);
	~CInvader(void);

	void setPos(Point p){p_pos = p;}
	Point getPos(){return p_pos;}

	void generateInvader();
	
	void draw();
};
