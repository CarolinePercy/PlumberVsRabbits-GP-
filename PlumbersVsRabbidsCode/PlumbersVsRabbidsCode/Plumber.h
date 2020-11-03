#pragma once
#include "Humanoid.h"

class Plumber : public Humanoid
{
public:
	Plumber(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name);
	Plumber();

	void ability(Humanoid enemy) override;
	void uniqueTurn(Humanoid enemyTeam[], int t_enemyTeamSize) override;
	void moveOne(Humanoid t_enemy);
	void moveAway(Humanoid t_enemy);
};

