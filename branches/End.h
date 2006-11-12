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

#ifndef _END_H_
#define _END_H_

class CEnd
{
protected:
	bool end;
	bool img[25];
public:
	CEnd(void);
	~CEnd(void);
	static CEnd* getInstance();

	void setEnd(bool e){end = e;}
	bool getEnd(){return end;}

	bool getImgAt(int p);

	void displayNothing();
	void displayWin();
	void displayLoose();
};

#endif
