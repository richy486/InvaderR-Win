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

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include ".\consts.h"
#include ".\invaderset.h"
#include ".\player.h"
#include ".\shooter.h"
#include ".\text.h"
#include ".\bomber.h"

int KeyDown[256];
int SpecDown[256];

CShooter shooter;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 480.0, 0.0, 320.0);
	
	srand( time(NULL));
	
	Point t_p;
	t_p.x = 10;
	t_p.y = 10;

	CInvaderSet::getInstance()->setPlaying(true);
	CInvaderSet::getInstance()->restart();
	
	CPlayer::getInstance()->start();
}
void checkKeyboard(void)
{
	if ( SpecDown[GLUT_KEY_LEFT] && CInvaderSet::getInstance()->getPlaying())
	{
		Point t_p = CPlayer::getInstance()->getPos();
		t_p.x -= 5;
		if(t_p.x > 20)
			CPlayer::getInstance()->setPos(t_p);
	}
	if ( SpecDown[GLUT_KEY_RIGHT] && CInvaderSet::getInstance()->getPlaying())
	{
		Point t_p = CPlayer::getInstance()->getPos();
		t_p.x += 5;
		if(t_p.x < 450)
			CPlayer::getInstance()->setPos(t_p);
	}
	if ( SpecDown[GLUT_KEY_F1] && CInvaderSet::getInstance()->getPlaying())
	{
		shooter.shoot(CPlayer::getInstance()->getPos());
	}//*/
}
static void timerCallback (int value) 
{ 
	/* Do timer processing */
	if(CInvaderSet::getInstance()->getPlaying())
	{
		CText::getInstance()->displayNothing();
		shooter.progress();
		CBomber::getInstance()->progress();
		CInvaderSet::getInstance()->move();
	}
	else
	{
		if(CInvaderSet::getInstance()->getOutcome())
			CText::getInstance()->displayWin();
		else
			CText::getInstance()->displayLoose();
	}
	
	checkKeyboard();
	/* maybe glutPostRedisplay(), if necessary */ 
	glutPostRedisplay();
	/* call back again after elapsedUSecs have passed */ 
	glutTimerFunc (FRAMERATE, timerCallback, 0); 
}

void OnDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	
	
	if(CInvaderSet::getInstance()->getPlaying())
	{
		CInvaderSet::getInstance()->drawSet();
		CPlayer::getInstance()->draw();
		shooter.draw();
		CBomber::getInstance()->draw();
	}
	else
	{
		shooter.killAll();
		CBomber::getInstance()->killAll();
		CInvaderSet::getInstance()->killAll();
		CText::getInstance()->draw();
	}
	glFlush();
	glutSwapBuffers();
}
void OnIdle(void)
{
	
}
void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) 
	{
	case 27:        // When Escape Is Pressed...
		exit ( 0 );   // Exit The Program
		break;        // Ready For Next Case
	case 90:
	case 90+32:
		shooter.shoot(CPlayer::getInstance()->getPos());
		break;
	case 13:
		if(!CInvaderSet::getInstance()->getPlaying())
		{
			CInvaderSet::getInstance()->setPlaying(true);
			CPlayer::getInstance()->start();
			CInvaderSet::getInstance()->restart();
		}
	default:        // Now Wrap It Up
		break;
	}
	KeyDown[key] = 1;
}
void keyboardUp(unsigned char key, int x, int y)
{
    KeyDown[key] = 0;
}
void specFunc(int key, int x, int y)
{
	SpecDown[key] = 1;
}
void specUpFunc(int key, int x, int y)
{
	SpecDown[key] = 0;
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(300, 300);
	glutInitWindowSize(480, 320);
	glutCreateWindow("invaderR");

	init();
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc( keyboardUp );
	glutSpecialFunc(specFunc);
	glutSpecialUpFunc(specUpFunc);
	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnIdle);
	glutTimerFunc(FRAMERATE, timerCallback, 0);
	glutMainLoop();
}