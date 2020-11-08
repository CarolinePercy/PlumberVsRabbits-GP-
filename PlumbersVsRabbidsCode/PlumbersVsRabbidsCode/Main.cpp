#include "Game.h"


int main()
{
	Game* game = new Game();

	// Main menu
	std::cout << "\tPLUMBERS VS RABBITS" << std::endl;
	std::cout << "The Rabbits and Plumbers are fighting over the Mush Kingdom! Help them defend their area!" << std::endl;
	std::cout << "Please enter whether you want to play as the Rabbit or the Plumbers (r/p)." << std::endl;
	std::cin >> game->input;

	// gets whether the player wants to play the rabbits or the plumbers
	while (game->input != 'p' && game->input != 'r')
	{
		Humanoid::errorMessage();
		std::cin >> game->input;
	}

	if (game->input == 'r') // if user selects rabbits, switch over bool
	{
		game->playingPlumbers = false;
	}

	while (game->gameInPlay)
	{
		system("CLS");
		while (game->inRound)
		{
			if (game->playingPlumbers) // how game will play if the user is playing as plumbers
			{
				game->plumbers[0]->playersTurn(game->rabbits);
				game->rabbits[0]->thoughtProcess(game->plumbers, 2);
				game->plumbers[1]->playersTurn(game->rabbits);
				game->rabbits[1]->thoughtProcess(game->plumbers, 2);
			}

			else // how the game will play if the user is playing as rabbits
			{
				game->plumbers[0]->thoughtProcess(game->rabbits, 2);
				game->rabbits[0]->playersTurn(game->plumbers);
				game->plumbers[1]->thoughtProcess(game->rabbits, 2);
				game->rabbits[1]->playersTurn(game->plumbers);
			}

			if (game->plumbers[0]->getHealth() == 0 && game->plumbers[1]->getHealth() == 0) // if both plumbers have died
			{
				game->inRound = false;
				std::cout << "\nRabbits won round " << game->round << "." << std::endl;
				Humanoid::letUserRead();
			}

			else if (game->rabbits[0]->getHealth() == 0 && game->rabbits[1]->getHealth() == 0) // if both rabbits have died
			{
				game->inRound = false;
				std::cout << "\nPlumbers won round " << game->round << "." << std::endl;
				Humanoid::letUserRead();
			}
		}

		while (!game->inRound) // while the player is still between rounds
		{
			system("CLS");
			std::cout << "You now have a moment to yourself after the round." << std::endl;
			std::cout << "You can decide to:\n" <<
				"1) Go to the shop to upgrade your weapons and characters,\n"
				<< "2) Continue on to the next round of the game,\n"
				<< "3) Close the game.\n\n" <<
				"Please enter the number corresponding to the selection." << std::endl;

			game->input = -1;
			std::cin >> game->input;

			while (game->input != '1' && game->input != '2' && game->input != '3') // if the user hasnt put in a correpsonding number, display error
			{
				Humanoid::errorMessage();
				std::cin >> game->input;
			}

			if (game->input == '1') // if user asked to go to shop
			{
				game->shop();
			}

			else if (game->input == '2') // if user asked to go to next round
			{
				game->inRound = true;
			}

			else // if user wants to close the game
			{
				game->inRound = true;
				game->gameInPlay = false;
			}

			game->round++;

			for (int i = 0; i < 2; i++) // resets all values so the rounds starts again properly
			{

				if (game->playingPlumbers) // increases the difficulty of the player's enemies
				{
					(*(Rabbit*)game->rabbits[i]).setDifficulty(game->round);
				}

				else
				{
					(*(Plumber*)game->plumbers[i]).setDifficulty(game->round);
				}

				//after both enemies and player have been upgraded, reset values
				(*(Plumber*)game->plumbers[i]).resetValues();
				(*(Rabbit*)game->rabbits[i]).resetValues();
			}
		}

	}
}