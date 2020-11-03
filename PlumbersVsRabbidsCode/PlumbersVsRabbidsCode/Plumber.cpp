#include "Plumber.h"

Plumber::Plumber(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name)
{
	health = 40;
	xPos = t_xPos;
	yPos = t_yPos;
	speed = 7;
	turnOrder = t_turnOrder;
	name = t_name;
}

Plumber::Plumber()
{
	health = 0;
	xPos = 0;
	yPos = 0;
	speed = 0;
	turnOrder = 0;
	name = "";
}

void Plumber::ability(Humanoid enemy)
{
	std::cout << name << " shot at " << enemy.name << "!" << std::endl;
	enemy.isHit(attackType::GUN);
}

void Plumber::uniqueTurn(Humanoid enemyTeam[], int t_index)
{
	int distance;
	bool shotEnemy{ false };

	for (int i{0}; i < speed; i++)
	{
		moveOne(enemyTeam[t_index]);
		distance = abs(distanceCalc(xPos, enemyTeam[t_index].getXPos()))
			+ abs(distanceCalc(yPos, enemyTeam[t_index].getYPos()));

		if (distance <= 2)
		{
			ability(enemyTeam[t_index]);
			shotEnemy = true;
		}

		if (shotEnemy)
		{
			moveAway(enemyTeam[abs(t_index - 1)]);
		}
	}

	std::cout << name << " ran away to (" << xPos << ", " << yPos << ")!" << std::endl;
}

void Plumber::moveOne(Humanoid t_enemy)
{
	if (t_enemy.getXPos() > xPos)
	{
		xPos++;
	}

	else if (t_enemy.getXPos < xPos)
	{
		xPos--;
	}

	else if (t_enemy.getYPos() > yPos)
	{
		yPos++;
	}
	else
	{
		yPos--;
	}
}

void Plumber::moveAway(Humanoid t_enemy)
{
	if (t_enemy.getXPos() > xPos)
	{
		move(xPos--, yPos);
	}

	else if (t_enemy.getXPos() < xPos)
	{
		move(xPos++, yPos);
	}

	else if (t_enemy.getYPos() > yPos)
	{
		move(xPos, yPos--);
	}

	else
	{
		move(xPos, yPos++);
	}
}

