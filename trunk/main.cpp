// version 2 is lost

#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include "consts.h"
#include ".\invaderset.h"
#include ".\player.h"
#include ".\shooter.h"

int KeyDown[256];
int SpecDown[256];
CPlayer player;
CShooter shooter;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 480.0, 0.0, 320.0);
	
	srand( time(NULL));
	
	Point t_p;
	t_p.x = 10;
	t_p.y = 10;
	
	//CInvaderSet::getInstance()->spawnNewSet();
	player.start();
}
void checkKeyboard(void)
{
	if ( SpecDown[GLUT_KEY_LEFT] )
	{
		Point t_p = player.getPos();
		t_p.x -= 5;
		if(t_p.x > 20)
			player.setPos(t_p);
	}
	if ( SpecDown[GLUT_KEY_RIGHT] )
	{
		Point t_p = player.getPos();
		t_p.x += 5;
		if(t_p.x < 450)
			player.setPos(t_p);
	}
	if ( SpecDown[GLUT_KEY_F1] )
	{
		shooter.shoot(player.getPos());
	}//*/
}
static void timerCallback (int value) 
{ 
	/* Do timer processing */
	
	shooter.progress();
	CInvaderSet::getInstance()->move();
	checkKeyboard();
	/* maybe glutPostRedisplay(), if necessary */ 
	glutPostRedisplay();
	/* call back again after elapsedUSecs have passed */ 
	glutTimerFunc (FRAMERATE, timerCallback, 0); 
}

void OnDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	
	CInvaderSet::getInstance()->drawSet();
	player.draw();
	shooter.draw();
	
	

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
		shooter.shoot(player.getPos());
		break;
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
	glutInitWindowPosition(50, 100);
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