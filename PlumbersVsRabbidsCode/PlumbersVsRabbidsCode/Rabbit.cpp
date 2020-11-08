#include "Rabbit.h"
/// <summary>
/// Rabbits constructor (inputs values)
/// </summary>
/// <param name="t_xPos">The starting x position of the rabbit</param>
/// <param name="t_yPos">the starting y position of the rabbit</param>
/// <param name="t_name">the name of the rabbit</param>
Rabbit::Rabbit(int t_xPos, int t_yPos, std::string t_name)
{
	totalHealth = 30;
	roundHealth = totalHealth;

	originalXPos = t_xPos;
	xPos = originalXPos;

	originalYPos = t_yPos;
	yPos = originalYPos;

	speed = 7;
	name = t_name;
}

/// <summary>
/// Rabbits constructor (used when making an array of rabbits)
/// </summary>
Rabbit::Rabbit()
{
	roundHealth = 0;
	xPos = 0;
	yPos = 0;
	speed = 0;
	name = "";
}

/// <summary>
/// Resets the values back to the original, used for new rounds
/// </summary>
void Rabbit::resetValues()
{
	xPos = originalXPos;
	yPos = originalYPos;
	roundHealth = totalHealth;
}

/// <summary>
/// If the character is within range of an enemy, it moves on top of it to attack, then run away
/// </summary>
/// <param name="enemyTeam">the enemy team</param>
/// <param name="enemyIndex">the index of the enemy to land on</param>
void Rabbit::uniqueTurn(Humanoid* enemyTeam[], int enemyIndex)
{
	xPos = enemyTeam[enemyIndex]->getXPos();
	yPos = enemyTeam[enemyIndex]->getYPos();

	std::cout << name << " ran up to " << enemyTeam[enemyIndex]->getName() << " and stabbed at them!" << std::endl;

	enemyTeam[enemyIndex]->isHit(attackType::KNIFE, attackAddition);
	ability(*enemyTeam[abs(enemyIndex - 1)]);
}

/// <summary>
/// Rabbit's ability is hitting an enemy, then running away. This is for the running away part
/// </summary>
/// <param name="enemy">The enemy that the rabbit is running away from</param>
void Rabbit::ability(Humanoid enemy)
{
	if (enemy.getXPos() > xPos)
	{
		xPos -= 3;
	}

	else if (enemy.getXPos() < xPos)
	{
		xPos += 3;
	}

	else if (enemy.getYPos() > yPos)
	{
		yPos -= 3;
	}

	else
	{
		yPos += 3;
	}

	std::cout << name << " hops away to (" << xPos << ", " << yPos << ")!" << std::endl;
	letUserRead();
}
