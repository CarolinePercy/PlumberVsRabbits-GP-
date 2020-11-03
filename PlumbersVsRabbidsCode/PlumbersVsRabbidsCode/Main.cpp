#include "Game.h"

void endscreen(bool plumbersWon, Plumber plumberTeam[], Rabbit rabbitTeam[]);

int main()
{
	return 0;	
}

/// <summary>
/// Displays the final results of the game
/// </summary>
void endscreen(bool plumbersWon, Plumber plumberTeam[], Rabbit rabbitTeam[])
{
	system("CLS");

	std::cout << "--------------------" << std::endl;
	std::cout << "| Name | Health | Won | Hits Taken | Hits Thrown |" << std::endl;

	for (int i{0}; i < 2; i++)
	{
		// First Plumbers 
		std::cout << "| " << plumberTeam[i].name << " | " << plumberTeam[i].getHealth() << " | ";
		if (plumbersWon)
		{
			std::cout << "Yes | ";
		}

		else
		{
			std::cout << "No | ";
		}

		std::cout << plumberTeam[i].getHitsTaken() << " | " << plumberTeam[i].getHitsThrown() << " |" << std::endl;

		// Then rabbits
		std::cout << "| " << rabbitTeam[i].name << " | " << rabbitTeam[i].getHealth() << " | ";
		if (plumbersWon)
		{
			std::cout << "No | ";
		}

		else
		{
			std::cout << "Yes | ";
		}

		std::cout << rabbitTeam[i].getHitsTaken() << " | " << rabbitTeam[i].getHitsThrown() << " |" << std::endl;
	}

	std::cout << "--------------------" << std::endl;
}