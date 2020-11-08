#include "Plumber.h"

/// <summary>
/// 
/// </summary>
/// <param name="t_xPos">New x position</param>
/// <param name="t_yPos">New y position</param>
/// <param name="t_name"></param>
Plumber::Plumber(int t_xPos, int t_yPos, std::string t_name)
{
	totalHealth = 40;
	roundHealth = totalHealth;

	originalXPos = t_xPos;
	xPos = originalXPos;

	originalYPos = t_yPos;
	yPos = originalYPos;

	speed = 4;
	name = t_name;
}

/// <summary>
/// Default constructor
/// </summary>
Plumber::Plumber()
{
	roundHealth = 0;
	xPos = 0;
	yPos = 0;
	speed = 0;
	name = "";
}

/// <summary>
/// Set the values back to the original. This is so rounds are reset
/// </summary>
void Plumber::resetValues()
{
	roundHealth = totalHealth;
	xPos = originalXPos;
	yPos = originalYPos;
}

/// <summary>
/// The ability of the Plumber. They shoot at the enemy from a farther distance
/// </summary>
/// <param name="enemy">The enemy to attack</param>
void Plumber::ability(Humanoid& enemy)
{
	std::cout << name << " shot at " << enemy.getName() << "!" << std::endl;
	enemy.isHit(attackType::GUN, attackAddition);
}

/// <summary>
/// Plumber's unique turn. Moves towards enemy, shoots at them, then runs away with their remaining speed
/// </summary>
/// <param name="enemyTeam">The enemy team</param>
/// <param name="t_index">The index of what is to be attacked</param>
void Plumber::uniqueTurn(Humanoid* enemyTeam[], int t_index)
{
	int distance = abs(distanceCalc(xPos, enemyTeam[t_index]->getXPos()))
		+ abs(distanceCalc(yPos, enemyTeam[t_index]->getYPos())); // distance value 

	bool shotEnemy{ false };

	for (int i{0}; i < speed; i++)
	{
		if (distance <= 2 && !shotEnemy) // if the character is within 2 spaces of the enemy and has not yet fired, fire at enemy
		{
			ability(*enemyTeam[t_index]);
			shotEnemy = true;
		}

		else if (!shotEnemy) // if the character hasnt shot enemy yet but not in range, run towards enemy
		{
			moveOne(*enemyTeam[t_index]);
			distance = abs(distanceCalc(xPos, enemyTeam[t_index]->getXPos()))
				+ abs(distanceCalc(yPos, enemyTeam[t_index]->getYPos()));
		}

		if (shotEnemy) // if character has shot enemy, run away 
		{
			moveAway(*enemyTeam[abs(t_index - 1)]);
		}
	}

	std::cout << name << " ran away to (" << xPos << ", " << yPos << ")!" << std::endl;
	letUserRead();
}

/// <summary>
/// Moves the character towards the enemy by 1
/// </summary>
/// <param name="t_enemy">Enemy to run towards</param>
void Plumber::moveOne(Humanoid t_enemy)
{
	if (t_enemy.getXPos() > xPos)
	{
		xPos++;
	}

	else if (t_enemy.getXPos() < xPos)
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

/// <summary>
/// Moves the character away from the enemy by 1
/// </summary>
/// <param name="t_enemy">Enemy to run away from</param>
void Plumber::moveAway(Humanoid t_enemy)
{
	if (t_enemy.getXPos() > xPos)
	{
		xPos--;
	}

	else if (t_enemy.getXPos() < xPos)
	{
		xPos++;
	}

	else if (t_enemy.getYPos() > yPos)
	{
		yPos--;
	}

	else
	{
		yPos++;
	}
}

