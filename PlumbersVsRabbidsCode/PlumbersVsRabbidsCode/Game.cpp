#include "Game.h"

Humanoid* Game::getHumanoid(int i)
{
	return plumbers[i];
}

Game::Game()
{
	bool gameInPlay{ true };
	bool playingPlumbers{ true };

	plumbers[0] = new Plumber(20, 30, 1, "Mario");
	plumbers[1] = new Plumber(40, 30, 3, "Luigi");
	rabbits[0] = new Rabbit(20, 60, 2, "Rabbit Peach");
	rabbits[1] = new Rabbit(40, 60, 4, "Rabbit Yoshi");


	while (gameInPlay)
	{
		if (playingPlumbers)
		{
			playersTurn(*((Plumber*)plumbers[0]));
			((Rabbit*)rabbits[0])->thoughtProcess(((Plumber*)plumbers), 2);
		}
	}
}

void Game::playersTurn(Humanoid playerChar)
{
	int actions = 3;
	bool moved{ false };
	bool attacked{ false };
	bool shielded{ false };
	bool healed{ false };
	char input{ ' ' };

	std::cout << playerChar.name << "'s turn!" << std::endl;

	std::cout << "To move, input 'm' (1 action)" << std::endl;
	std::cout << "To attack, input 'a' (1-3 actions)" << std::endl;
	std::cout << "To shield, input 's' (1-3 actions)" << std::endl;
	std::cout << "To heal, input 'h' (1 action)" << std::endl;

	while (actions > 0)
	{
		std::cout << "You have three actions left." << std::endl;
		
		std::cin >> input;

		while (input != 'm' && input != 'a' && input != 's' && input != 'h')
		{
			errorMessage();
			std::cin >> input;
		}
	}


}

void Game::errorMessage()
{
	std::cout << "Please enter a valid command." << std::endl;
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}

void Game::playerMove(Humanoid playerChar)
{
	bool correctMovement{ false };
	int xMove;
	int yMove;
	bool error{ true };

	std::cout << "Please input the x coordinate, then hit enter," << std::endl;
	std::cout <<"and then enter the y coordinate to move to." << std::endl;


	while (!correctMovement)
	{
		while (error)
		{
			try
			{
				std::cin >> xMove;
				error = false;
			}

			catch (int e)
			{
				errorMessage();
				error = true;
			}
		}

		error = true;

		while (error)
		{
			try
			{
				std::cin >> yMove;
				error = false;
			}

			catch (int e)
			{
				errorMessage();
				error = true;
			}
		}

		correctMovement = playerChar.withinRangeCheck(xMove, yMove);

		if (correctMovement)
		{
			std::cout << "" << std::endl;
		}

		else
		{
			std::cout "" << std::endl;
		}
	}
}
