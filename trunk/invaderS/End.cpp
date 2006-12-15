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

#include "End.h"

CEnd::CEnd(void)
{
}

CEnd::~CEnd(void)
{
}
CEnd* CEnd::getInstance()
{
	static CEnd instance;
    return &instance;
}
bool CEnd::getImgAt(int p)
{
	if(p >= 0 && p < 25) 
		return img[p]; 
	else 
		return 0;
}
// Set the image to nothing
void CEnd::displayNothing()
{
	for(int i = 0; i < 25; i++)
	{
		img[i] = false;
	}
}
// Set the image to :)
void CEnd::displayWin()
{
	for(int i = 0; i < 25; i++)
	{
		img[i] = false;
	}
	img[5] = true;
	img[15] = true;
	img[8] = true;
	img[13] = true;
	img[18] = true;
	img[2] = true;
	img[22] = true;

}
// Set the image to :(
void CEnd::displayLoose()
{
	for(int i = 0; i < 25; i++)
	{
		img[i] = false;
	}
	img[5] = true;
	img[15] = true;
	img[7] = true;
	img[12] = true;
	img[17] = true;
	img[3] = true;
	img[23] = true;
}