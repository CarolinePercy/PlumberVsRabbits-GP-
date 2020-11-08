#include "Game.h"

/// <summary>
/// Game contructor
/// </summary>
Game::Game()
{
	plumbers[0] = new Plumber(20, 40, "Mario");
	plumbers[1] = new Plumber(30, 40, "Luigi");
	rabbits[0] = new Rabbit(20, 50, "Rabbit Peach");
	rabbits[1] = new Rabbit(30, 50, "Rabbit Yoshi");
}
/// <summary>
/// Function that controls the shop menu between rounds
/// </summary>
void Game::shop()
{
	bool inShop{ true };
	int input = -1;

	while (inShop) // while user stays on shop menu
	{
		system("CLS");
		std::cout << "\tSHOP" << std::endl;
		std::cout << "1) Health increase by 10: 10 coins" << std::endl;
		std::cout << "2) Damage increase by 5: 20 coins" << std::endl;
		std::cout << "3) Shield increase 10: 30 coins" << std::endl;
		std::cout << "4) Leave shop." << std::endl;
		std::cout << "Your Wallet: " << Humanoid::coinBag.contents() << " coins."<< std::endl;

		std::cin >> input;

		while (input < 1 || input > 4) // if user didnt input a correct number, give error
		{
			Humanoid::errorMessage();
			std::cin >> input;
		}

		switch (input) // switch is used to pass the right info into the next method
		{
		case 1:
			purchase(10, 0);
			break;
		case 2:
			purchase(20, 1);
			break;
		case 3:
			purchase(30, 2);
			break;
		case 4:
			inShop = false;
			break;
		default:
			std::cout << "ERROR in shop!!" << std::endl;
			break;
		}
	}
}

/// <summary>
/// Figures out what the user is purchasing, and whether they have the coins to purchase it.
/// </summary>
/// <param name="purchaseCost">The cost of that product</param>
/// <param name="whatWasPurchased">The number related to what upgrade the player bought</param>
void Game::purchase(int purchaseCost, int whatWasPurchased)
{
	if (Humanoid::coinBag.contents() >= purchaseCost) // If the user can afford the item
	{
		Humanoid::coinBag.buy(purchaseCost); // remove the coins from account
		 
		if (playingPlumbers) // if the user chose plumbers, upgrade plumbers, else upgrade rabbits
		{
			((Plumber*)plumbers[0])->upgrade((improvement)whatWasPurchased);
			((Plumber*)plumbers[1])->upgrade((improvement)whatWasPurchased);
		}

		else
		{
			((Rabbit*)rabbits[0])->upgrade((improvement)whatWasPurchased);
			((Rabbit*)rabbits[1])->upgrade((improvement)whatWasPurchased);
		}
	}
	else // tells user they cant afford the item
	{
		std::cout << "You do not have enough money for that!" << std::endl;
		Humanoid::letUserRead();
	}
}
