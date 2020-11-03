#pragma once
#include "Humanoid.h"

class Rabbit : public Humanoid
{
public:

	// Constructors
	Rabbit(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name);
	Rabbit();

	void uniqueTurn(Humanoid enemyTeam[], int t_enemyTeamSize) override;
	void ability(Humanoid enemy) override;
};

