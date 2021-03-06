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
#include "shooter.h"
#include "end.h"

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
int gKeyCtrl;
int gKeyEnter;

int startAmount = 20;
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
	gKeyCtrl = 0;
	gKeyEnter = 0;

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

	CInvaderSet::getInstance()->createBasicInvaders(startAmount);

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
		if(!CEnd::getInstance()->getEnd())
		{
			if (gKeyLeft) 
				CPlayer::getInstance()->subMove(THRUST);
			if (gKeyRight) 
				CPlayer::getInstance()->addMove(THRUST);
			if (gKeyCtrl || SDL_JoystickGetButton(gJoystick, 2)) 
				CPlayer::getInstance()->shoot();
		}

		if (!gKeyCtrl && !SDL_JoystickGetButton(gJoystick, 2)) 
			CPlayer::getInstance()->readyShoot();

		if (gKeyEnter || SDL_JoystickGetButton(gJoystick, 0))
		{
			for (int i = 0; i < HEIGHT; i++)
			{
				for (int j = 0; j < WIDTH; j++)
				{
				  drawrect(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE, BGCOLOR, false);
				}
			}
			CInvaderSet::getInstance()->clearInvaders();
			CBomber::getInstance()->clearBombs();
			CShooter::getInstance()->clearShots();
			CInvaderSet::getInstance()->createBasicInvaders(startAmount);
			CPlayer::getInstance()->makeImg();
			CPlayer::getInstance()->start();
			CPlayer::getInstance()->setMove(0);
		}

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

	// Find mates
	CInvaderSet::getInstance()->findClosestMates();

	// do action on invaders
	CInvaderSet::getInstance()->actionInvaders();

	// move bombs
	CBomber::getInstance()->progress();

	// move shots
	CShooter::getInstance()->progress();

	// test for shot hits with invaders (this should be in CShooter class)
	point2D p;
	for(int i = 0; i < CShooter::getInstance()->getNumShots(); i++)
	{
		p = CShooter::getInstance()->getShotPos(i);
		if(CInvaderSet::getInstance()->testHits(p))
		{
			CShooter::getInstance()->destroyShot(i);
		}
	}

	// win!
	if(CInvaderSet::getInstance()->getNumInvaders() == 0)
	{
		CEnd::getInstance()->setEnd(true);
		CEnd::getInstance()->displayWin();
	}
	// loose
	else if(CPlayer::getInstance()->getBlocks() == 0)
	{
		CEnd::getInstance()->setEnd(true);
		CEnd::getInstance()->displayLoose();
	}
	// playing
	else
	{
		CEnd::getInstance()->setEnd(false);
	}


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
		  drawrect(j * TILESIZE, i * TILESIZE, TILESIZE, TILESIZE, BGCOLOR, false);
		}
	}
	//drawrect(0, 0, LEVELWIDTH, LEVELHEIGHT, BGCOLOR, false);

	// draw invaders
	point2D p;
	unsigned int invaderColour;
	for(int i = 0; i < CInvaderSet::getInstance()->getNumInvaders(); i++)
	{
		//if(CInvaderSet::getInstance()->getInvaderSex(i) == MALE)
			invaderColour = M_INVADERCOLOR;
		//else
			//invaderColour = F_INVADERCOLOR;

		p = CInvaderSet::getInstance()->getInvaderPos(i);
		for(int j = 0; j < 25; j++)
		{
			if(CInvaderSet::getInstance()->getInvaderImgAtWM(i,j))
			{
				drawrect( ((int)p.x+((j/5)*IPS))-(IPS*2.5f), ((int)p.y+((j%5)*IPS))-(IPS*2.5f), IPS, IPS, invaderColour, true);
			}
		}

	}

	// draw invaders' lines
	/*point2D po;
	for(int i = 0; i < CInvaderSet::getInstance()->getNumInvaders(); i++)
	{
		if(CInvaderSet::getInstance()->getInvaderSex(i) == MALE)
			invaderColour = M_INVADERCOLOR;
		else
			invaderColour = F_INVADERCOLOR;

		for(double t = 0.0; t <= 1.0; t+=0.01)
		{
			if(t <= 0.0)
				t = 0.0;
			if(t >= 1.0)
				t = 1.0;
			po.x = CInvaderSet::getInstance()->getInvaderLIP(i,0).x*pow((1-t),2) 
				+ 2*t*(1-t)*CInvaderSet::getInstance()->getInvaderLIP(i,1).x 
				+ CInvaderSet::getInstance()->getInvaderLIP(i,2).x*pow(t,2);
			po.y = CInvaderSet::getInstance()->getInvaderLIP(i,0).y*pow((1-t),2) 
				+ 2*t*(1-t)*CInvaderSet::getInstance()->getInvaderLIP(i,1).y 
				+ CInvaderSet::getInstance()->getInvaderLIP(i,2).y*pow(t,2);

			drawrect( (int)po.x, (int)po.y, 1, 1, invaderColour, true);
		}

	}*/

	// draw the player object
	p = CPlayer::getInstance()->getPos();
	for(int i = 0; i < 25; i++)
	{
		if(CPlayer::getInstance()->getImgAt(i))
			drawrect( ((int)p.x+((i/5)*IPS))-(IPS*2.5f), ((int)p.y+((i%5)*IPS))-(IPS*2.5f), IPS, IPS, PLAYERCOLOR, true);
	}
	//cout << p.x << " " << p.y << "\n";
    
	// draw bombs
	for(int i = 0; i < CBomber::getInstance()->getNumBombs(); i++)
	{
		p = CBomber::getInstance()->getBombPos(i);
		drawrect( (int)p.x-(IPS/2), (int)p.y-(IPS/2), IPS, IPS, M_INVADERCOLOR, true);
	}

	// draw shots
	for(int i = 0; i < CShooter::getInstance()->getNumShots(); i++)
	{
		p = CShooter::getInstance()->getShotPos(i);
		drawrect( (int)p.x-(IPS/2), (int)p.y-(IPS/2), IPS, IPS, SHOTCOLOUR, true);
	}

	// draw win loose
	if(CEnd::getInstance()->getEnd())
	{
		for(int i = 0; i < 25; i++)
		{
			if(CEnd::getInstance()->getImgAt(i))
				drawrect( ((i/5)*TPS)+2.5*TPS, ((i%5)*TPS)+TPS, TPS, TPS, ENDCOLOUR, true);
		}
	}

	// Unlock if needed
	if (SDL_MUSTLOCK(gScreen)) 
	SDL_UnlockSurface(gScreen);

	// Tell SDL to update the whole gScreen
	SDL_UpdateRect(gScreen, 0, 0, WIDTH, HEIGHT);  
}


// Entry point
#ifdef __cplusplus
	extern "C"
#endif
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
			if(event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_LEFT)
				{
					gKeyLeft = 1;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{
					gKeyRight = 1;
				}
				else if(event.key.keysym.sym == SDLK_LCTRL)
				{
					gKeyCtrl = 1;
				}
				else if(event.key.keysym.sym == SDLK_RETURN)
				{
					gKeyEnter = 1;
				}
			}
			else if(event.type == SDL_KEYUP)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
				{
					return 0;
				}
				else if(event.key.keysym.sym == SDLK_LEFT)
				{
					gKeyLeft = 0;
				}
				else if(event.key.keysym.sym == SDLK_RIGHT)
				{
					gKeyRight = 0;
				}
				else if(event.key.keysym.sym == SDLK_LCTRL)
				{
					gKeyCtrl = 0;
				}
				else if(event.key.keysym.sym == SDLK_RETURN)
				{
					gKeyEnter = 0;
				}
			}
			else if(event.type == SDL_QUIT)
			{
				return(0);
			}
		}// end while poll event
	}// end while 1
	return 0;
}