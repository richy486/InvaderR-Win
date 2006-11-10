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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#if defined(_MSC_VER)
#include "SDL.h"
#else
#include "SDL/SDL.h"
#endif
#include "common.h"
#include "InvaderSet.h"

// Screen surface  
SDL_Surface *gScreen;

// Pointer to the joystick interface
SDL_Joystick *gJoystick = NULL;



// Last iteration's tick value
int gLastTick;
// Player's position
float gXPos;
float gYPos;
// Player's motion vector
float gXMov;
float gYMov;

// Player's key status
int gKeyLeft;
int gKeyRight;
int gKeyUp;
int gKeyDown;

// Level data
unsigned char gLevel[LEVELWIDTH * LEVELHEIGHT] =
{
  0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
  0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,
  0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,
  1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,
  1,1,1,1,1,0,1,0,1,1,1,0,1,1,1
};

void drawcircle(int x, int y, int r, int c)
{
  int i, j;
  for (i = 0; i < 2 * r; i++)
  {
    // vertical clipping: (top and bottom)
    if ((y - r + i) >= 0 && (y - r + i) < HEIGHT)
    {
      int len = (int)sqrt((float)(r * r - (r - i) * (r - i))) * 2;
      int xofs = x - len / 2;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= WIDTH)
      {
        len -= (xofs + len) - WIDTH;
      }
      int ofs = (y - r + i) * PITCH + xofs;
      
      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; j++)
        ((unsigned int*)gScreen->pixels)[ofs + j] = c;
    }
  }
}


void drawrect(int x, int y, int width, int height, int c)
{
  int i, j;
  for (i = 0; i < height; i++)
  {
    // vertical clipping: (top and bottom)
    if ((y + i) >= 0 && (y + i) < HEIGHT)
    {
      int len = width;
      int xofs = x;

      // left border
      if (xofs < 0)
      {
        len += xofs;
        xofs = 0;
      }

      // right border
      if (xofs + len >= WIDTH)
      {
        len -= (xofs + len) - WIDTH;
      }
      int ofs = (i + y) * PITCH + xofs;

      // note that len may be 0 at this point, 
      // and no pixels get drawn!
      for (j = 0; j < len; j++)
        ((unsigned int*)gScreen->pixels)[ofs + j] = c;
    }
  }
}


void init()
{
	gXPos = WIDTH / 2;
	gYPos = HEIGHT - (PLAYERAREA/2);// / 2;
	gXMov = 0;
	gYMov = 0;

	gKeyLeft = 0;
	gKeyRight = 0;
	gKeyUp = 0;
	gKeyDown = 0;

	if (SDL_NumJoysticks() > 0)
	{
		gJoystick = SDL_JoystickOpen(0);		
		if (SDL_JoystickNumAxes(gJoystick) < 2)
		{
			// Not enough axes for our use; don't use the joystick.
			SDL_JoystickClose(gJoystick);
			gJoystick = NULL;
		}
	}

	CInvaderSet::getInstance()->createBasicInvaders(5);

	gLastTick = SDL_GetTicks(); 
}

void deinit()
{
  if (gJoystick)
    SDL_JoystickClose(gJoystick);
}

void render()
{   
  // Ask SDL for the time in milliseconds
  int tick = SDL_GetTicks();

  if (tick <= gLastTick) 
  {
    SDL_Delay(1);
    return;
  }

  while (gLastTick < tick)
  {
    if (gKeyLeft) gXMov -= THRUST;
    if (gKeyRight) gXMov += THRUST;
    if (gKeyUp) gYMov -= THRUST;
    if (gKeyDown) gYMov += THRUST;

	if (gJoystick)
    {
      gXMov += (SDL_JoystickGetAxis(gJoystick, 0) / 32768.0f) * THRUST;
      gYMov += (SDL_JoystickGetAxis(gJoystick, 1) / 32768.0f) * THRUST;
    }

    gXMov *= SLOWDOWN;
    gYMov *= SLOWDOWN;

    gXPos += gXMov;
    gYPos += gYMov;

	//if (gLevel[(((int)gYPos) / TILESIZE) * LEVELWIDTH + ((int)gXPos) / TILESIZE] == 0)
	//{
	//	// player fell off - reset position
	//	gXPos = WIDTH / 2;
	//	gYPos = HEIGHT / 2;
	//}

	// Collision with the screen borders
    if (gXPos > WIDTH - RADIUS)
    {
      gXPos -= gXMov;
      gXMov = -gXMov * COLLISIONSLOWDOWN;
    }

    if (gXPos < RADIUS)
    {
      gXPos -= gXMov;
      gXMov = -gXMov * COLLISIONSLOWDOWN;
    }

    if (gYPos > HEIGHT - RADIUS)
    {
      gYPos -= gYMov;
      gYMov = -gYMov * COLLISIONSLOWDOWN;
    }

    if (gYPos < RADIUS)
    {
      gYPos -= gYMov;
      gYMov = -gYMov * COLLISIONSLOWDOWN;
    }

    gLastTick += 1000 / PHYSICSFPS;
  }

  // Lock surface if needed
  if (SDL_MUSTLOCK(gScreen))
    if (SDL_LockSurface(gScreen) < 0) 
      return;

  // fill background
  for (int i = 0; i < LEVELHEIGHT; i++)
  {
    for (int j = 0; j < LEVELWIDTH; j++)
    {
      drawrect(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE, 
               gLevel[i * LEVELWIDTH + j] ? 1 : FALLCOLOR);
    }
  }
  
  // draw borders
 /* drawrect(0, 0, WIDTH, 8, WALLCOLOR);         
  drawrect(0, 0, 8, HEIGHT, WALLCOLOR);         
  drawrect(WIDTH - 8, 0, 8, HEIGHT, WALLCOLOR);         
  drawrect(0, HEIGHT - 8, WIDTH, 8, WALLCOLOR);  */   

	// move invaders
  CInvaderSet::getInstance()->moveInvaders();

  // draw invaders
  point2D p;
  for(int i = 0; i < CInvaderSet::getInstance()->getNumInvaders(); i++)
  {
		p = CInvaderSet::getInstance()->getInvaderPos(i);
		drawrect((int)p.x, (int)p.y, 5, 5, WALLCOLOR);
		//cout << p.x << " " << p.y << "\n";

  }

  // draw the player object
  drawcircle((int)gXPos,
             (int)gYPos,
             RADIUS,
             BALLCOLOR);
        
  // Unlock if needed
  if (SDL_MUSTLOCK(gScreen)) 
    SDL_UnlockSurface(gScreen);

  // Tell SDL to update the whole gScreen
  SDL_UpdateRect(gScreen, 0, 0, WIDTH, HEIGHT);  
}


// Entry point
int main(int argc, char *argv[])
{
	srand( time(NULL));

	// Initialize SDL's subsystems
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) 
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// Register SDL_Quit to be called at exit; makes sure things are
	// cleaned up when we quit.
	atexit(SDL_Quit);

	// make sure our deinit gets called at shutdown.
	atexit(deinit);

	// Attempt to create a WIDTHxHEIGHT window with 32bit pixels.
	gScreen = SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_SWSURFACE);

	init();

	// If we fail, return error.
	if (gScreen == NULL) 
	{
		fprintf(stderr, "Unable to set up video: %s\n", SDL_GetError());
		exit(1);
	}

  // Main loop: loop forever.
  while (1)
  {
    // Render stuff
    render();

    // Poll for events, and handle the ones we care about.
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
      switch (event.type) 
      {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
          gKeyLeft = 1;
          break;
        case SDLK_RIGHT:
          gKeyRight = 1;
          break;
        /*case SDLK_UP:
          gKeyUp = 1;
          break;
        case SDLK_DOWN:
          gKeyDown = 1;*/
          break;
        }
        break;

      case SDL_KEYUP:          
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
          // If escape is pressed, return (and thus, quit)
          return 0;
        case SDLK_LEFT:
          gKeyLeft = 0;
          break;
        case SDLK_RIGHT:
          gKeyRight = 0;
          break;
        /*case SDLK_UP:
          gKeyUp = 0;
          break;
        case SDLK_DOWN:
          gKeyDown = 0;*/
          break;
        }
        break;

      case SDL_QUIT:
        return(0);
      }
    }
  }
  return 0;
}