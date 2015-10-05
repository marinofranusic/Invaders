#include "Enemy.h"
#include "DiceInvaders.h"
Enemy::Enemy() {
	
}
Enemy::~Enemy() {
	
}
void Enemy::create(int newType, int newX, int newY, IDiceInvaders* sys)
{
	if (newType == 1)
	{
		sprite = sys->createSprite("data/enemy1.bmp");
	}
	else //just else to avoid any errors...
	{
		sprite = sys->createSprite("data/enemy2.bmp");
	}
	
	sprite->draw(newX, newY);
	type = newType;
	x = newX;
	y = newY;
	//when creating object it will move to the right so direction is 1
	//and reaching the right border which will set toggle to true
	//so at create time it should be false
	toggle = false;
	direction = 1;
}

void Enemy::draw() {
	sprite->draw(x, y);
}

void Enemy::stepDown(bool newToggle)
{
	//Toggling the flag and lowering the object by 30px
	if (newToggle != toggle)
	{
		toggle = !toggle;
		y += 30;
	}
}

int Enemy::getType() {
	return type;
}
void Enemy::setType(int newType) {
	type = newType;
}

int Enemy::getXPos() {
	return x;
}
void Enemy::setXPos(int newX) {
	x = newX;
	
}
int Enemy::getYPos() {
	return y;
}
void Enemy::setYPos(int newY) {
	y = newY;
}
int Enemy::getDirection()
{
	return direction;
}
void Enemy::setDirection(int dir)
{
	direction = dir;
}