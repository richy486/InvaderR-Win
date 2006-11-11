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
#include "player.h"
#include "bomber.h"

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

unsigned int blend_avg(unsigned int source, unsigned int target)
{
  unsigned int sourcer = (source >>  0) & 0xff;
  unsigned int sourceg = (source >>  8) & 0xff;
  unsigned int sourceb = (source >> 16) & 0xff;
  unsigned int targetr = (target >>  0) & 0xfd;
  unsigned int targetg = (target >>  8) & 0xfd;
  unsigned int targetb = (target >> 16) & 0xfd;

  targetr = (sourcer + targetr) / 2.1f;
  targetg = (sourceg + targetg) / 2.1f;
  targetb = (sourceb + targetb) / 2.1f;

  return (targetr <<  0) |
         (targetg <<  8) |
         (targetb << 16);
}
unsigned int blend_mul(unsigned int source, unsigned int target)
{
  unsigned int sourcer = (source >>  0) & 0xff;
  unsigned int sourceg = (source >>  8) & 0xff;
  unsigned int sourceb = (source >> 16) & 0xff;
  unsigned int targetr = (target >>  0) & 0xff;
  unsigned int targetg = (target >>  8) & 0xff;
  unsigned int targetb = (target >> 16) & 0xff;

  targetr = (sourcer * targetr) >> 8;
  targetg = (sourceg * targetg) >> 8;
  targetb = (sourceb * targetb) >> 8;

  return (targetr <<  0) |
         (targetg <<  8) |
         (targetb << 16);
}
unsigned int blend_add(unsigned int source, unsigned int target)
{
  unsigned int sourcer = (source >>  0) & 0xff;
  unsigned int sourceg = (source >>  8) & 0xff;
  unsigned int sourceb = (source >> 16) & 0xff;
  unsigned int targetr = (target >>  0) & 0xff;
  unsigned int targetg = (target >>  8) & 0xff;
  unsigned int targetb = (target >> 16) & 0xff;

  targetr += sourcer;
  targetg += sourceg;
  targetb += sourceb;

  if (targetr > 0xff) targetr = 0xff;
  if (targetg > 0xff) targetg = 0xff;
  if (targetb > 0xff) targetb = 0xff;

  return (targetr <<  0) |
         (targetg <<  8) |
         (targetb << 16);
}
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


void drawrect(int x, int y, int width, int height, int c, bool avg)
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
	  {
		  if(avg == false)
		  {
			((unsigned int*)gScreen->pixels)[ofs + j] = c;
			//((unsigned int*)gScreen->pixels)[ofs + j] = blend_avg(((unsigned int*)gScreen->pixels)[ofs + j], c);
		  }
		  else
		  {
			  ((unsigned int*)gScreen->pixels)[ofs + j] = blend_add(((unsigned int*)gScreen->pixels)[ofs + j], c);
		  }

	  }
    }
  }
}


void init()
{
	CPlayer::getInstance()->start();
	CPlayer::getInstance()->setMove(0);
	
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

	CInvaderSet::getInstance()->createBasicInvaders(1);

	gLastTick = SDL_GetTicks(); 
}

void deinit()
{
  if (gJoystick)
    SDL_JoystickClose(gJoystick);
}
void exe()
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
		if (gKeyLeft) CPlayer::getInstance()->subMove(THRUST);
		if (gKeyRight) CPlayer::getInstance()->addMove(THRUST);

		if (gJoystick)
		{
		  CPlayer::getInstance()->addMove((SDL_JoystickGetAxis(gJoystick, 0) / 32768.0f) * THRUST);
		}

		CPlayer::getInstance()->slowdown();
		CPlayer::getInstance()->posPlusMove();

		// Collision with the screen borders
		if (CPlayer::getInstance()->getPos().x > WIDTH - RADIUS)
		{
			CPlayer::getInstance()->posMinusMove();
			CPlayer::getInstance()->setMove(-CPlayer::getInstance()->getMove() * COLLISIONSLOWDOWN);
		}

		if (CPlayer::getInstance()->getPos().x < RADIUS)
		{
			CPlayer::getInstance()->posMinusMove();
			CPlayer::getInstance()->setMove(-CPlayer::getInstance()->getMove() * COLLISIONSLOWDOWN);
		}

		gLastTick += 1000 / PHYSICSFPS;
	}

	// move invaders
	CInvaderSet::getInstance()->moveInvaders();

	// do action on invaders
	CInvaderSet::getInstance()->actionInvaders();

	// move bombs
	CBomber::getInstance()->progress();
}
void render()
{   
	// Lock surface if needed
  if (SDL_MUSTLOCK(gScreen))
    if (SDL_LockSurface(gScreen) < 0) 
      return;

	// fill background
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
		  drawrect(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE, 
				   BGCOLOR, false);
		}
	}
	//drawrect(0, 0, LEVELWIDTH, LEVELHEIGHT, BGCOLOR, false);

	// draw invaders
	point2D p;
	for(int i = 0; i < CInvaderSet::getInstance()->getNumInvaders(); i++)
	{
		p = CInvaderSet::getInstance()->getInvaderPos(i);
		for(int j = 0; j < 25; j++)
		{
			if(CInvaderSet::getInstance()->getInvaderImgAtWM(i,j))
				drawrect( ((int)p.x+((j/5)*IPS))-(IPS*2.5f), ((int)p.y+((j%5)*IPS))-(IPS*2.5f), IPS, IPS, INVADERCOLOR, true);
		}

	}

	// draw the player object
	p = CPlayer::getInstance()->getPos();
	for(int i = 0; i < 25; i++)
	{
		if(CPlayer::getInstance()->getImgAt(i))
			drawrect( ((int)p.x+((i/5)*IPS))-(IPS*2.5f), ((int)p.y+((i%5)*IPS))-(IPS*2.5f), IPS, IPS, PLAYERCOLOR, true);
	}
    
	// draw bombs
	for(int i = 0; i < CBomber::getInstance()->getNumBombs(); i++)
	{
		p = CBomber::getInstance()->getBombPos(i);
		drawrect( (int)p.x-(IPS/2), (int)p.y-(IPS/2), IPS, IPS, BOMBCOLOR, true);
	}

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
		// execute movement
		exe();
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
				}
				break;

			case SDL_QUIT:
				return(0);
			}
		}
  }
  return 0;
}