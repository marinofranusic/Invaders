#include "DiceInvaders.h"
class Player {

public:

	Player();
	~Player();
	//coordinates
	int getXPos();
	void setXPos(int x);
	int getYPos();
	void setYPos(int y);
	//get-set-ers for players remaining lives
	int getLives();
	void setLives(int num);
	//get-set-ers for players score
	int getScore();
	void setScore(int num);
	void create(int x, int y, IDiceInvaders* sys);
	void draw();

protected:
	int lives;
	bool alive;
	int x, y;
	ISprite* sprite;
	int score;
};
