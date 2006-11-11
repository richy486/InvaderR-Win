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