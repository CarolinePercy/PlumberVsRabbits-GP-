#pragma once
#include "Rabbit.h"
#include "Plumber.h"
class Game
{
public:
	bool gameInPlay{ true }; // Whether the game is still open, aka if this was false, the window would close
	bool inRound{ true }; // Bool that tracks whether the player is in game (aka turnbased combat) or at the window where they have the option to go to the shop
	bool playingPlumbers{ true }; // Bool that keeps track on which team the user is playing as
	bool plumbersWon{ true }; // Whether the plumbers or rabbits won
	char input{' '}; // Used for all input from the player
	int round{ 1 }; // The rounds of the game

	Humanoid* plumbers[2]; // Amount of plumbers in game
	Humanoid* rabbits[2]; // amount of rabbits in game
	Game();

	void shop();
	void purchase(int purchaseCost, int whatWasPurchased);
};