#include ".\base.h"

CBase::CBase(void)
{
}

CBase::~CBase(void)
{
}
// Create the base image.
void CBase::generate()
{
	for(int i = 0; i < 25; i++)
	{
		img[i] = true;
	}
	img[4] = false;
	img[24] = false;
	img[5] = false;
	img[10] = false;
	img[15] = false;
}
// Test if any of the pixels of the base have been hit.
bool CBase::testHit(Point p)
{
	p.x+=1.5;
	if(p.y >=50 && p.y <=50+(5*IPS))
	{
		for(int i = 0; i < 25; i++)
		{
			if(p.x >= p_pos.x+((i/5)*IPS) && p.x <= p_pos.x+((i/5)*IPS)+IPS
				&& p.y >= (p_pos.y)+((i%5)*IPS) && p.y <= (p_pos.y)+((i%5)*IPS)+IPS
				&& img[i] == true)
			{
				img[i] = false;
				return true;
			}
		}
	}
	return false;
}
// Draw the base.
void CBase::drawBase()
{
	glColor3f(0.9, 0.9, 0.9);
	for(int i = 0; i < 25; i++)
	{
		if(img[i] == true)
		{
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