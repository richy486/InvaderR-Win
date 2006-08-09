#include ".\invader.h"


CInvader::CInvader(void)
{
}

CInvader::~CInvader(void)
{
}
void CInvader::generateInvader()
{
	for(int i = 0; i < 15; i++)
	{
		img[i] = rand()%2;
	}
}
void CInvader::remakeInvader()
{

}

void CInvader::draw()
{
	for(int i = 0; i < 15; i++)
	{
		if(img[i] == true)
		{
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
				glVertex2i(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS));
				glVertex2i(p_pos.x+((i/5)*IPS)+IPS,	(p_pos.y)+((i%5)*IPS));
				glVertex2i(p_pos.x+((i/5)*IPS)+IPS,	(p_pos.y)+((i%5)*IPS)+IPS);
				glVertex2i(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS)+IPS);
				glVertex2i(p_pos.x+((i/5)*IPS),		(p_pos.y)+((i%5)*IPS));
			glEnd();

			if(i < 5)
			{
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
					glVertex2i(p_pos.x+((i/5)*IPS)+(4*IPS),		(p_pos.y)+((i%5)*IPS));
					glVertex2i(p_pos.x+((i/5)*IPS)+IPS+(4*IPS),	(p_pos.y)+((i%5)*IPS));
					glVertex2i(p_pos.x+((i/5)*IPS)+IPS+(4*IPS),	(p_pos.y)+((i%5)*IPS)+IPS);
					glVertex2i(p_pos.x+((i/5)*IPS)+(4*IPS),		(p_pos.y)+((i%5)*IPS)+IPS);
					glVertex2i(p_pos.x+((i/5)*IPS)+(4*IPS),		(p_pos.y)+((i%5)*IPS));
				glEnd();
			}
			if(i >= 5 && i < 10)
			{
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_POLYGON);
					glVertex2i(p_pos.x+((i/5)*IPS)+(2*IPS),		(p_pos.y)+((i%5)*IPS));
					glVertex2i(p_pos.x+((i/5)*IPS)+IPS+(2*IPS),	(p_pos.y)+((i%5)*IPS));
					glVertex2i(p_pos.x+((i/5)*IPS)+IPS+(2*IPS),	(p_pos.y)+((i%5)*IPS)+IPS);
					glVertex2i(p_pos.x+((i/5)*IPS)+(2*IPS),		(p_pos.y)+((i%5)*IPS)+IPS);
					glVertex2i(p_pos.x+((i/5)*IPS)+(2*IPS),		(p_pos.y)+((i%5)*IPS));
				glEnd();
			}//*/
		}
	}

	
}