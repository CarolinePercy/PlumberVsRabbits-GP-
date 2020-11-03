#pragma once
#include "Rabbit.h"
#include "Plumber.h"
class Game
{
public:
	Humanoid* plumbers[2];
	Humanoid* rabbits[2];
	Humanoid* getHumanoid(int i);
	Game();

	void playersTurn(Humanoid playerChar);
	void errorMessage();

	void playerMove(Humanoid playerChar);
	void playerAttack(Humanoid playerChar);
	void playerShield(Humanoid playerChar);
	void playerHeal(Humanoid playerChar);
};

