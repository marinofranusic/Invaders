#include "DiceInvaders.h"
class Bomb {

public:
	Bomb();
	~Bomb();
	//get-set-ers for object position 
	int getXPos();
	void setXPos(int x);
	int getYPos();
	void setYPos(int y);
	//Creates object on the screen at specified coordinates
	void create(int x, int y, IDiceInvaders* sys);
	//Draws the object
	void draw();

protected:
	int x, y;
	ISprite* sprite;
};