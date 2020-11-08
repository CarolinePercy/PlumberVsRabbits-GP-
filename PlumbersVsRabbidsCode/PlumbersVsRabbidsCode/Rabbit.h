#pragma once
#include "Humanoid.h"

class Rabbit : public Humanoid
{
private:
	// Overriden Methods
	void uniqueTurn(Humanoid* enemyTeam[], int t_enemyTeamSize) override;
	void ability(Humanoid enemy) override;
public:
	// Constructors
	Rabbit(int t_xPos, int t_yPos, std::string t_name);
	Rabbit();

	// Misc method
	void resetValues();
};

