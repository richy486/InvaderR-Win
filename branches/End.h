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
