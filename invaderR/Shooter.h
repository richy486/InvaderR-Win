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

//#include <GL/glut.h>
#include <list>
using namespace std;
#include ".\invaderset.h"
#include ".\consts.h"
#include ".\baseset.h"

class CShooter
{
protected:
	list<Point> shots;
public:
	CShooter(void);
	~CShooter(void);

	void shoot(Point p);
	void progress(float seconds);
	void killAll();
	void draw();
};
