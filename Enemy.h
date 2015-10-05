#include "DiceInvaders.h"
class Enemy {

public:

	Enemy();
	~Enemy();
	//get-set-ers for object type,position and direction of movement
	//type defines type of an enemy
	//currently just to types that differ only in the bitmap
	//type=1 - Enemy1.bmp
	//type=2 - Enemy2.bmp
	int getType();
	void setType(int type);
	int getXPos();
	void setXPos(int x);
	int getYPos();
	void setYPos(int y);
	//direction defines if the enemy is moving left or right
	//direction=1 - moving right
	//direction=-1 - moving left
	int getDirection();
	void setDirection(int dir);
	void create(int type, int x, int y, IDiceInvaders* sys);
	void draw();
	//Steps the enemy down when reaching the screen limit
	//Uses true when reaching right border and false when reaching left border
	//toggle used to prevent multiple stepdowns
	void stepDown(bool newToggle);

protected:
	int type;
	bool alive;
	int x, y;
	ISprite* sprite;
	bool toggle;
	int direction;
};