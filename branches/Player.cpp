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
	for(int i = 0; i < 15; i++)
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
	if(p >= 0 && p <= 15) 
		return img[p]; 
	else 
		return 0;
}
bool CPlayer::getImgAtWM(int p)
{
	if(p >= 0 && p < 15) 
		return img[p]; 
	else if(p >= 15 && p < 20)
		return img[p-10];
	else if(p >= 20 && p < 25)
		return img[p-20];
	else 
		return 0;
}