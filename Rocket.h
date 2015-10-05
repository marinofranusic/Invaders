#include "DiceInvaders.h"
class Rocket {

public:
	//Class that could be the same with bomb but created a new one 
	//for possible future changes
	Rocket();
	~Rocket();
	
	int getXPos();
	void setXPos(int x);
	int getYPos();
	void setYPos(int y);

	void create(int x, int y, IDiceInvaders* sys);
	void draw();

protected:

	int x, y;
	ISprite* sprite;
};