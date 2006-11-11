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

#include "Player.h"

CPlayer::CPlayer(void)
{
	for(int i = 0; i < 25; i++)
	{
		img[i] = false;
	}
	img[3] = true;
	img[4] = true;
	img[6] = true;
	img[7] = true;
	img[8] = true;
	img[10] = true;
	img[11] = true;
	img[12] = true;
	img[13] = true;
	img[16] = true;
	img[17] = true;
	img[18] = true;
	img[23] = true;
	img[24] = true;
}

CPlayer::~CPlayer(void)
{
}
CPlayer* CPlayer::getInstance()
{
	static CPlayer instance;
    return &instance;
}
// Put the player in the start position.
void CPlayer::start()
{
	pos.x = WIDTH / 2;
	pos.y = HEIGHT - (PLAYERAREA/2);
}
bool CPlayer::getImgAt(int p)
{
	if(p >= 0 && p < 25) 
		return img[p]; 
	else 
		return 0;
}
bool CPlayer::testHit(point2D p)
{
	// check if it is within the 5*5 range of the player
	/*if( p.x+(IPS/2) >= pos.x-(2.5*IPS) && p.x-(IPS/2) <= pos.x+(2.5*IPS) &&
		p.y+(IPS/2) >= pos.y-(2.5*IPS) && p.y-(IPS/2) <= pos.y+(2.5*IPS) )
	{*/
		for(int i = 0; i < 25; i++)
		{
			//p.x >= p_pos.x+((i/5)*IPS)	&& p.x <= p_pos.x+((i/5)*IPS)+IPS
			//p.y >= p_pos.y+((i%5)*IPS)	&& p.y <= p_pos.y+((i%5)*IPS)+IPS
			if( p.x >= (pos.x+((i/5)*IPS))-(IPS*2.5f) && p.x <= (pos.x+((i/5)*IPS))-(IPS*2.5f)+IPS &&
				p.y >= (pos.y+((i%5)*IPS))-(IPS*2.5f) && p.y <= (pos.y+((i%5)*IPS))-(IPS*2.5f)+IPS &&
				img[i] == true)
			{
				img[i] = false;
				return true;
			}
		}
	//}
	//else
	return false;
}