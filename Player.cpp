#include ".\player.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
}
void CPlayer::start()
{
	p_pos.x = 230;
	p_pos.y = 10;
}
void CPlayer::draw()
{
	for(int i = 0; i < 25; i++)
	{
		if(1 == 1)
		{
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
				glVertex2i(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS));
				glVertex2i(p_pos.x+((i/5)*IPS)+IPS,	(p_pos.y)+((i%5)*IPS));
				glVertex2i(p_pos.x+((i/5)*IPS)+IPS,	(p_pos.y)+((i%5)*IPS)+IPS);
				glVertex2i(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS)+IPS);
				glVertex2i(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS));
			glEnd();
		}
	}
}