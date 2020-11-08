#pragma once
#include "Humanoid.h"

class Plumber : public Humanoid
{
private:
	// Unique / overriden methods
	void ability(Humanoid& enemy);
	void uniqueTurn(Humanoid* enemyTeam[], int t_enemyTeamSize) override;
	void moveOne(Humanoid t_enemy);
	void moveAway(Humanoid t_enemy);
public:
	// Constructors
	Plumber(int t_xPos, int t_yPos, std::string t_name);
	Plumber();

	// Misc method
	void resetValues();
};

