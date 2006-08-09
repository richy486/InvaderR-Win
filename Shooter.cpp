#include ".\shooter.h"

CShooter::CShooter(void)
{
}

CShooter::~CShooter(void)
{
}
void CShooter::shoot(Point p)
{
	Point t_p;
	t_p.x = p.x +(2.5*IPS);
	t_p.y = p.y +(5*IPS);
	shots.push_back(t_p);
}
void CShooter::progress()
{
	list<Point>::iterator iter;

	iter=shots.begin(); 
	while(iter!=shots.end())
	{
		Point t_p;
		t_p.x = iter->x;
		t_p.y = iter->y;
		if(iter->y >= 320 || CInvaderSet::getInstance()->testHits(t_p) )// && iter != shots.end() && iter != shots.begin())
		{
			iter = shots.erase(iter);
		}
		else
		{
			iter->y +=5;
			iter++; 
		}
		
	}
}

void CShooter::draw()
{
	list<Point>::iterator iter;
	for(iter=shots.begin(); iter!=shots.end(); ++iter)
	{
		glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POLYGON);
				glVertex2i(iter->x,		(iter->y));
				glVertex2i(iter->x+IPS,	(iter->y));
				glVertex2i(iter->x+IPS,	(iter->y)+IPS);
				glVertex2i(iter->x,		(iter->y)+IPS);
				glVertex2i(iter->x,		(iter->y));
			glEnd();
	}
}