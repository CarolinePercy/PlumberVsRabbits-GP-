#include "Rabbit.h"
/// <summary>
/// Rabbits constructor (inputs values)
/// </summary>
/// <param name="t_xPos">The starting x position of the rabbit</param>
/// <param name="t_yPos">the starting y position of the rabbit</param>
/// <param name="t_turnOrder">the turn order for the rabbit</param>
/// <param name="t_name">the name of the rabbit</param>
Rabbit::Rabbit(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name)
{
	health = 30;
	xPos = t_xPos;
	yPos = t_yPos;
	speed = 4;
	turnOrder = t_turnOrder;
	name = t_name;
}

/// <summary>
/// Rabbits constructor (used when making an array of rabbits)
/// </summary>
Rabbit::Rabbit()
{
	health = 0;
	xPos = 0;
	yPos = 0;
	speed = 0;
	turnOrder = 0;
	name = "";
}

void Rabbit::uniqueTurn(Humanoid enemyTeam[], int enemyIndex)
{
	move(enemyTeam[enemyIndex].getXPos(), enemyTeam[enemyIndex].getYPos());

	std::cout << name << " ran up to " << enemyTeam[enemyIndex].name << " and stabbed at them!" << std::endl;

	enemyTeam[enemyIndex].isHit(attackType::KNIFE);
	hitsThrown++;
	ability(enemyTeam[abs(enemyIndex - 1)]);
}

void Rabbit::ability(Humanoid enemy)
{
	if (enemy.getXPos() > xPos)
	{
		move(xPos - 3, yPos);
	}

	else if (enemy.getXPos() < xPos)
	{
		move(xPos + 3, yPos);
	}

	else if (enemy.getYPos() > yPos)
	{
		move(xPos, yPos - 3);
	}

	else
	{
		move(xPos, yPos + 3);
	}

	std::cout << name << " hops away to (" << xPos << ", " << yPos << ")!" << std::endl;
}
