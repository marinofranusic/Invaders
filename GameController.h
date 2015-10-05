#include "DiceInvaders.h"
#include <vector>
#include "Enemy.h"
#include "Bomb.h"
#include "Rocket.h"
#include "Player.h"
class GameController {

public:

	GameController();
	~GameController();

	//Creates and positions alien ships on the screen
	void SetupAliens(std::vector<Enemy>& e, IDiceInvaders* system);

	//Function to draw all the sprites on screen
	void DrawSprites(std::vector<Enemy>& e, std::vector<Bomb>& b, std::vector<Rocket>& r, Player* p);

	//Function for writing the score and remaining lives on top of the screen
	void WriteTopline(Player* p, IDiceInvaders* sys);

	//Updates positions of the alien ships
	void UpdateAliens(std::vector<Enemy>& e, Player* p, float* sumTime);

	//Updates positions of the rockets
	void UpdateRockets(std::vector<Rocket>& r, float* sumTime);

	//Updates positions of the bombs
	void UpdateBombs(std::vector<Bomb>& b, float* sumTime);

	//Creates and fires rockets from the player ship
	void FireRocket(std::vector<Rocket>& r, Player* p, IDiceInvaders* sys);

	//Function that will randomly drop the bomb from a random alien ship
	void DropBombs(std::vector<Enemy>& e, std::vector<Bomb>& b, IDiceInvaders* sys);

	//Checks if there is a collision between any rocket and any alien ship
	void RocketCollider(std::vector<Enemy>& e, std::vector<Rocket>& r, Player* p);

	//Checks if there is a collision between any bomb and the player
	void BombCollider(std::vector<Bomb>& b, Player* p);
	
	//Checks if there is a collision between any alien ship and the player
	void AlienCollider(std::vector<Enemy>& e, Player* p);
		
	//Gives message about game over and achieved score
	void GameOver(Player* p, IDiceInvaders* sys);
	
	//incereases the level (speed and probability for bombs)
	void IncreaseLevel(float* sumTime);

	int GetWidth();
	int GetHeight();

protected:
	int bombRandomizing; 
	float alienSpeed;
	int width = 640;
	int height = 480;
};