#include <windows.h>
#include <cassert>
#include <cstdio>
#include <ctime>
#include <vector>
#include "DiceInvadersLib.h"
#include "DiceInvaders.h"
#include "GameController.h"

int main()
{
	srand((unsigned)time(0));

	//Disables the console window
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, 0);

	DiceInvadersLib lib("DiceInvaders.dll");
	IDiceInvaders* system = lib.get();

	//Creates object instances and vectors for objects that can appear in multiple instances
	Player player;
	std::vector<Rocket> rockets;
	std::vector<Enemy> aliens;
	std::vector<Bomb> bombs;
	GameController gc;

	//Initializes the screen
	system->init(gc.GetWidth(), gc.GetHeight());

	//Setup aliens on screen
	gc.SetupAliens(aliens, system);

	//Create player on screen
	player.create(int(gc.GetWidth() /2), gc.GetHeight() - 32,system);
	float horizontalPosition = 320;
	float lastTime = system->getElapsedTime();
	float sumTime = 0;
	float sumTimeRocket = 0;
	float sumTimeBomb = 0;
	float timeLastRocket = 0;
	float sumTimeLevel = 0;
	while (system->update())
	{
		//Goes through all the game functions if player has enough lives
		//otherwise it's game over.
		if (player.getLives() > 0)
		{
			float newTime = system->getElapsedTime();

			//Moves the player to new horizontal position that is changed by keypress capture
			//Limits the value to the visible area 
			if (int(horizontalPosition) > gc.GetWidth() - 32)
				horizontalPosition = float(gc.GetWidth() - 32);
			else if (int(horizontalPosition) < 0)
				horizontalPosition = 0;
			player.setXPos(int(horizontalPosition));

			//Calculates helper variables for timed executions
			float move = (newTime - lastTime) * 160.0f;
			sumTime += (newTime - lastTime);
			sumTimeRocket += (newTime - lastTime);
			sumTimeBomb += (newTime - lastTime);
			sumTimeLevel+= (newTime - lastTime);
			lastTime = newTime;
			
			//Calls functions in Game controller class
			//Detailed description in GameController.h
			gc.WriteTopline(&player, system);
			gc.DrawSprites(aliens, bombs, rockets, &player);
			gc.DropBombs(aliens, bombs, system);
			gc.RocketCollider(aliens, rockets, &player);
			//If the size of vector holding alien ship objects is 0 setup the new arsenal of ships
			if (aliens.size() == 0)
				gc.SetupAliens(aliens, system);
			gc.BombCollider(bombs, &player);
			gc.UpdateAliens(aliens, &player, &sumTime);
			gc.AlienCollider(aliens, &player);
			gc.UpdateRockets(rockets, &sumTimeRocket);
			gc.UpdateBombs(bombs, &sumTimeBomb);
			gc.IncreaseLevel(&sumTimeLevel);

			//Captures keypresses
			IDiceInvaders::KeyStatus keys;
			system->getKeyStatus(keys);
			if (keys.right)
				horizontalPosition += move;
			else if (keys.left)
				horizontalPosition -= move;
			else if (keys.fire)
			{
				//Fires rocket if more than 0.2 seconds passed from the last launch
				//Limits too fast firing of rockets if space is held pressed
				if (newTime - timeLastRocket > 0.2)
				{
					gc.FireRocket(rockets, &player, system);
					timeLastRocket = newTime;
				}
			}
		}
		else
		{
			gc.GameOver(&player, system);
		}
	}
	
	system->destroy();
	
	return 0;
}



