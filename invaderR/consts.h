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

#include <iostream>
#include <stdio.h>
using std::string;
using std::cout;

#if defined USE_GLUT
	#include <GL/glut.h>
#else
	#include <windows.h>
	#include <gl\gl.h>
	#include <gl\glu.h>
#endif

// size of a invader pixel
#define IPS 3
// size of a win/loose pixel
#define TPS 50
// time between glutTimerFunc calls
#define FRAMERATE 15
//position on the screen
struct Point
{
	float x;
	float y;
};




