#include "Player.h"
#include "DiceInvaders.h"

Player::Player() {

}
Player::~Player() {

}
void Player::create(int newX, int newY, IDiceInvaders* sys)
{
	sprite = sys->createSprite("data/Player.bmp");
	sprite->draw(newX, newY);
	x = newX;
	y = newY;
	//at creation time the player should have three lives and score 0
	lives = 3;
	score = 0;
}

void Player::draw() 
{
	sprite->draw(x, y);
}

int Player::getXPos() 
{
	return x;
}
void Player::setXPos(int newX) 
{
	x = newX;
}
int Player::getYPos() 
{
	return y;
}
void Player::setYPos(int newY) 
{
	y = newY;
}
int Player::getLives()
{
	return lives;
}
void Player::setLives(int num)
{
	lives = num;
}
int Player::getScore()
{
	return score;
}
void Player::setScore(int num)
{
	score = num;
}
