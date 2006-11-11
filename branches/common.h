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

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stdio.h>

using namespace std;

// Screen pitch
#define PITCH (gScreen->pitch / 4)
// Screen width
#define WIDTH 480
// Screen height
#define HEIGHT 320
// player area
#define PLAYERAREA 40
// Color of player's ball
#define BALLCOLOR 0x007fff
// Radius of the player's ball
#define RADIUS 12
// Background color
#define BGCOLOR 0x000000
// Invader color
#define INVADERCOLOR 0x9f1f1f
// Player color
#define PLAYERCOLOR 0x1F3D9F
// Definition of PI
#define PI 3.1415926535897932384626433832795f
// Player's thrust value
#define THRUST 0.5f
// Slowdown due to friction, etc.
#define SLOWDOWN 0.89f
// Slowdown due to collision
#define COLLISIONSLOWDOWN 0.9f
// Physics iterations per second
#define PHYSICSFPS 100

// Width of level data
#define LEVELWIDTH 15
// Height of level data
#define LEVELHEIGHT 10

// Tile size (width and height)
#define TILESIZE 32
// size of a invader pixel
#define IPS 5

struct point2D{double x; double y;};
struct point3D{double x; double y; double z;};

#endif