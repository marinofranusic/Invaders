#include "Bomb.h"
#include "DiceInvaders.h"

Bomb::Bomb() {

}
Bomb::~Bomb() {
	
}
void Bomb::create(int newX, int newY, IDiceInvaders* sys)
{
	//Creates a sprite with the given bmp file on screen
	sprite = sys->createSprite("data/bomb.bmp");
	//Draws the sprite on screen
	sprite->draw(newX, newY);
	x = newX;
	y = newY;
}

void Bomb::draw() {
	sprite->draw(x, y);
}

int Bomb::getXPos() {
	return x;
}
void Bomb::setXPos(int newX) {
	x = newX;
}
int Bomb::getYPos() {
	return y;
}
void Bomb::setYPos(int newY) {
	y = newY;
}