#include "GameController.h"
#include "DiceInvaders.h"

const int timeForLevelUp = 2; //time until aliens speed up and start generating more bombs

GameController::GameController() {
	bombRandomizing = 1000; //Smaller number indicates more chance for alien to drop a bomb
	alienSpeed = 0.2f; //Smaller number increases the movement speed of the aliens
}
GameController::~GameController() {

}

int GameController::GetWidth()
{
	return width;
}
int GameController::GetHeight()
{
	return height;
}

void GameController::DrawSprites(std::vector<Enemy>& e, std::vector<Bomb>& b, std::vector<Rocket>& r, Player* p)
{
	//Loop through all the objects and draw them on screen
	for (unsigned i = 0; i < e.size(); i++)
	{
		Enemy &tempEnemy = e[i];
		tempEnemy.draw();
	}
	for (unsigned i = 0; i < b.size(); i++)
	{
		Bomb &tempBomb = b[i];
		tempBomb.draw();
	}
	for (unsigned i = 0; i < r.size(); i++)
	{
		Rocket &tempRocket = r[i];
		tempRocket.draw();
	}
	p->draw();
}

void GameController::WriteTopline(Player* p, IDiceInvaders* sys)
{
	char a[40];
	sprintf_s(a, 20, "Lives: %d", p->getLives());
	sys->drawText(0, 0, a);
	sprintf_s(a, 20, "Score: %d", p->getScore());
	sys->drawText(width - 80, 0, a);
}

void GameController::DropBombs(std::vector<Enemy>& e, std::vector<Bomb>& b, IDiceInvaders* sys)
{
	//Gets a random number between 1 and bombRandomizing
	//The smaller the number bombRandomizing is, higher the chances of getting a bomb
	int rndNum = 1 + rand() / (RAND_MAX / (bombRandomizing - 1 + 1) + 1);
	//77 is arbitrarily chosen number
	if (rndNum == 77)
	{
		Bomb tempBomb;
		//if there are any enemies available and if there are less then 5 bombs currently on screen
		if (e.size() > 0 && b.size() < 5)
		{
			//get a random number in the range of 1 and number of alien ships
			int alienRndNum = 0 + rand() / (RAND_MAX / (e.size() - 1 + 1) + 1);
			//drops a bomb from the position of a randomly chosen ship
			tempBomb.create(e[alienRndNum].getXPos(), e[alienRndNum].getYPos() + 32, sys);
			b.push_back(tempBomb);
		}
	}
}

void GameController::RocketCollider(std::vector<Enemy>& e, std::vector<Rocket>& r, Player* p)
{
	//Loop through all the enemies in vector
	for (unsigned i = 0; i < e.size(); i++)
	{
		Enemy &tempEnemy = e[i];
		//for each ship loop through all the rockets currently on screen
		for (unsigned j = 0; j < r.size(); j++)
		{
			Rocket &tempRocket = r[j];
			//checks if there is a intesection between object positions
			if (tempRocket.getXPos() >= tempEnemy.getXPos() - 22 &&
				tempRocket.getXPos() <= tempEnemy.getXPos() + 22 &&
				tempRocket.getYPos() <= tempEnemy.getYPos() + 32 &&
				tempRocket.getYPos() >= tempEnemy.getYPos())
			{
				//removes rocket and the ship it collided with, updates the score
				r.erase(r.begin() + j);
				e.erase(e.begin() + i);
				p->setScore(p->getScore() + 10);
				break;
			}
		}
	}
}

void GameController::BombCollider(std::vector<Bomb>& b, Player* p)
{
	//Loops through all the bombs in the vector
	for (unsigned i = 0; i < b.size(); i++)
	{
		Bomb &tempBomb = b[i];
		//checks if there is a intesection between object positions
		if (tempBomb.getXPos() >= p->getXPos() - 22 &&
			tempBomb.getXPos() <= p->getXPos() + 22 &&
			tempBomb.getYPos() <= p->getYPos() + 32 &&
			tempBomb.getYPos() >= p->getYPos())
		{
			//remove one life from the player and remove the bomb that hit him
			p->setLives(p->getLives() - 1);
			b.erase(b.begin() + i);
		}
	}
}

void GameController::UpdateAliens(std::vector<Enemy>& e, Player* p, float* sumTime)
{
	//Ships are moved 10px horizontally
	int alienMove = 10;
	//loops through all the ships
	for (unsigned i = 0; i < e.size(); i++)
	{
		//checks if any of the ships is close to the right edge
		if (e[i].getXPos() + 32 > width-10)
		{
			//if the edge is reached go through all the ships
			//set their direction to -1 (go left)
			//and step them down with flag true (right edge)
			for (unsigned j = 0; j < e.size(); j++)
			{
				e[j].setDirection(-1);
				e[j].stepDown(true);
			}
			break;
		}
		//checks if any of the ships is close to the left edge
		if (e[i].getXPos() < 10)
		{
			//if the edge is reached go through all the ships
			//set their direction to 1 (go right)
			//and step them down with flag false (left edge)
			for (unsigned j = 0; j < e.size(); j++)
			{
				e[j].setDirection(1);
				e[j].stepDown(false);
			}
			
			break;
		}
		//checks if any of the ships reached the bottom of the screen 
		if (e[i].getYPos() > height - 32)
		{
			//in this case player automatically loses the game
			p->setLives(0);
			break;
		}
	}
	//Uses the pointer to the helper variable from main function
	//to determine when should the ships move
	//the movement will occur when the sum is alienSpeed (0.2f)
	//reset the sum to 0 at the end
	if (*sumTime > alienSpeed)
	{
		for (unsigned i = 0; i < e.size(); i++)
		{
			//move every ship alienMove pixels to the left or right
			//depending or direction (moving to left is direction -1 which will reduce x position
			e[i].setXPos(e[i].getXPos() + alienMove*e[i].getDirection());
		}
		*sumTime = 0;
	}
}

void GameController::AlienCollider(std::vector<Enemy>& e, Player* p)
{
	for (unsigned i = 0; i < e.size(); i++)
	{	//Loops through all the alien ships, checks for overlapping 	
		Enemy &tempEnemy = e[i];
		if (p->getXPos() >= tempEnemy.getXPos() - 32 &&
			p->getXPos() <= tempEnemy.getXPos() + 32 &&
			p->getYPos() <= tempEnemy.getYPos() + 32 &&
			p->getYPos() >= tempEnemy.getYPos())
		{
			//remove that alien ship and reduce one life from the player
			e.erase(e.begin() + i);
			p->setLives(p->getLives() - 1);
			break;
		}
	}
}

void GameController::UpdateRockets(std::vector<Rocket>& r, float* sumTime)
{
	//Uses the pointer to the helper variable from main function
	//to determine when should the rockets move
	//the movement will occur when the sum is 0.02f
	//reset the sum to 0 at the end
	if (*sumTime > 0.02)
	{
		for (unsigned i = 0; i < r.size(); i++)
		{
			//moves the rocket straight up, so just reduces y position
			//if y position is less than 0 (top of screen) remove that rocket
			Rocket &tempRocket = r[i];
			tempRocket.setYPos(tempRocket.getYPos() - 10);
			if (tempRocket.getYPos() < 0)
			{
				r.erase(r.begin() + i);
			}
		}
		*sumTime = 0;
	}
}

void GameController::UpdateBombs(std::vector<Bomb>& b, float* sumTime)
{
	//Uses the pointer to the helper variable from main function
	//to determine when should the rockets move
	//the movement will occur when the sum is 0.09f (bombs move much slower than players rocket)
	//reset the sum to 0 at the end
	if (*sumTime > 0.09)
	{
		for (unsigned i = 0; i < b.size(); i++)
		{
			//moves the bomb straight down, so just increase y position
			//if y position is more than height (bottom of screen) remove that bomb
			Bomb &tempBomb = b[i];
			tempBomb.setYPos(tempBomb.getYPos() + 10);
			if (tempBomb.getYPos() > height)
			{
				b.erase(b.begin() + i);
			}
		}
		*sumTime = 0;
	}
}

void GameController::FireRocket(std::vector<Rocket>& r, Player* p, IDiceInvaders* sys)
{
	Rocket tempRocket;
	//creates the rocket object if there are less than 5 rockets
	//5 is just chosen to make the game harder
	if (r.size() <5)
	{
		tempRocket.create(p->getXPos(), p->getYPos() - 32, sys);
		r.push_back(tempRocket);

	}
}

void GameController::GameOver(Player* p, IDiceInvaders* sys)
{
	//displays the messages on the screen
	sys->drawText(int(width / 2) - 60, int(height / 2) - 80, "G A M E   O V E R !");
	char a[30];
	sprintf_s(a, 30, "Your score was: %d", p->getScore());
	sys->drawText(int(width / 2) - 70, int(height / 2), a);
}

void GameController::SetupAliens(std::vector<Enemy>& e, IDiceInvaders* system)
{
	//creates 19 ships (number of ships need to make the wanted formation)
	for (int i = 0; i <= 18; i++)
	{
		Enemy tempEnemy;
		e.push_back(tempEnemy);
	}
	//creates the objects and designated locations
	e[0].create(1, 50, 30, system);
	e[1].create(1, 98, 30, system);
	e[2].create(1, 146, 30, system);
	e[3].create(2, 242, 30, system);
	e[4].create(2, 210, 60, system);
	e[5].create(2, 268, 60, system);
	e[6].create(1, 5, 90, system);
	e[7].create(1, 53, 90, system);
	e[8].create(1, 101, 90, system);
	e[9].create(2, 178, 90, system);
	e[10].create(2, 300, 90, system);
	e[11].create(1, 37, 120, system);
	e[12].create(2, 146, 120, system);
	e[13].create(2, 242, 120, system);
	e[14].create(2, 330, 120, system);
	e[15].create(1, 5, 150, system);
	e[16].create(1, 53, 150, system);
	e[17].create(1, 114, 150, system);
	e[18].create(2, 360, 150, system);
}

void GameController::IncreaseLevel(float* sumTime)
{
	//Uses the pointer to the helper variable from main function
	//to determine when should the rockets move
	//the movement will occur when the sum is timeForLevelUp (2 sec)
	//reset the sum to 0 at the end
	if (*sumTime > timeForLevelUp)
	{
		//reduce the time interval for alien movement which increases their speed
		if (alienSpeed > 0.02)
			alienSpeed -= 0.005f;
		//reduce the random number interval increasing the probability to get the bomb
		if (bombRandomizing > 300)
			bombRandomizing -= 200;
		*sumTime = 0;
	}
}