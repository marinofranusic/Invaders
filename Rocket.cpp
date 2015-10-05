#include "Rocket.h"
#include "DiceInvaders.h"

Rocket::Rocket() {

}
Rocket::~Rocket() {
	
}
void Rocket::create(int newX, int newY, IDiceInvaders* sys)
{
	sprite = sys->createSprite("data/rocket.bmp");
	
	sprite->draw(newX, newY);
	setXPos(newX);
	setYPos(newY);
}

void Rocket::draw() {
	sprite->draw(x, y);
}


int Rocket::getXPos() {
	return x;
}
void Rocket::setXPos(int newX) {
	x = newX;
}
int Rocket::getYPos() {
	return y;
}
void Rocket::setYPos(int newY) {
	y = newY;
}