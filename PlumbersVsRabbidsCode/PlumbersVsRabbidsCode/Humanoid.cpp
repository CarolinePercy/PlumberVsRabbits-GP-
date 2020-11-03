#include "Humanoid.h"


/// <summary>
/// Moves the character to the x and y location passed to it
/// </summary>
/// <param name="t_newX">The X position to move to</param>
/// <param name="t_newY">The Y position to move to</param>
void Humanoid::move(int t_newX, int t_newY)
{
	if (speed >= t_newX + t_newY)
	{
		xPos = t_newX;
		yPos = t_newY;
	}

	else
	{
		std::cout << "They're unable to travel that far." << std::endl;
	}
}

/// <summary>
/// Gets the x position of the current character 
/// </summary>
/// <returns>X position of the character</returns>
int Humanoid::getXPos()
{
	return xPos;
}

/// <summary>
/// Gets the y position of the current character
/// </summary>
/// <returns>Y position of the character</returns>
int Humanoid::getYPos()
{
	return yPos;
}

int Humanoid::getHitsTaken()
{
	return hitsTaken;
}

int Humanoid::getHitsThrown()
{
	return hitsThrown;
}

int Humanoid::getHealth()
{
	return health;
}

int Humanoid::getTurnOrder()
{
	return turnOrder;
}

/// <summary>
/// Calculates the amount of health the character would lose, given the damage the attacker did, and the strength of their defence.
/// </summary>
/// <param name="t_damage">The damage done by the attacker</param>
void Humanoid::isHit(attackType t_damageType)
{
	int damage = 0;
	hitsTaken++;

	switch (t_damageType)
	{
	case attackType::PUNCH:
		damage = 10;
		break;
	case attackType::KNIFE:
		damage = 15;
		break;
	case attackType::AXE:
		damage = 20;
		break;
	case attackType::GUN:
		damage = 5;
		break;
	default:
		break;
	}

	damage = damageCalc(damage);

	health -= damage;

	std::cout << name << " lost " << damage << " HP!" << std::endl;

	if (health <= 0)
	{
		health = 0;
		std::cout << name << " is dead!" << std::endl;
	}

	else
	{
		std::cout << name << " remaining HP: " << health << std::endl;
	}
}

/// <summary>
/// If the units decides to shield this turn,
/// changes the shield variable in the character
/// </summary>
/// <param name="t_newShieldType">The new shield the character will use</param>
void Humanoid::defend(shieldStrength t_newShieldType)
{
	currentShield = t_newShieldType;
}

/// <summary>
/// Calculates how much damage is done,
/// when considering the type of attack and type of shield
/// </summary>
/// <param name="t_rawDamage">the amount of damage done,
/// if the enemy has no shield</param>
/// <returns>returns the damage that the character will suffer after it goes through shield</returns>
int Humanoid::damageCalc(int t_rawDamage)
{
	int percentageRemoved = 0;
	int damageRemoved;

	switch (currentShield)
	{
	case shieldStrength::SMALL:
		percentageRemoved = 33;
		break;
	case shieldStrength::MEDIUM:
		percentageRemoved = 66;
		break;
	case shieldStrength::LARGE:
		percentageRemoved = 100;
		break;
	default:
		break;
	}

	damageRemoved = (t_rawDamage / 100) * percentageRemoved;

	t_rawDamage = t_rawDamage - damageRemoved;

	return t_rawDamage;
}

/// <summary>
/// Checks whether an enemy is in range of the character to hit
/// </summary>
/// <param name="t_enemyXPos">The enemy x position</param>
/// <param name="t_enemyYPos">the enemy y position</param>
/// <returns></returns>
bool Humanoid::withinRangeCheck(int t_enemyXPos, int t_enemyYPos)
{
	int xDistance = abs(distanceCalc(xPos, t_enemyXPos));
	int yDistance = abs(distanceCalc(yPos, t_enemyYPos));

	if (xDistance + yDistance > speed)
	{
		return false;
	}

	else
	{
		return true;
	}
}

/// <summary>
/// Calculates the distance between two positions
/// </summary>
/// <param name="t_enemyDistance">the enemy position (x or y)</param>
/// <param name="t_allyDistance">the current character's position (x or y)</param>
/// <returns></returns>
int Humanoid::distanceCalc(int t_enemyDistance, int t_allyDistance)
{
	return t_enemyDistance - t_allyDistance;
}

/// <summary>
/// 
/// </summary>
/// <param name="enemyTeam">the enemy team array</param>
/// <param name="t_enemyTeamSize">the size of the enemy team array</param>
/// <returns>index of the closest enemy</returns>
int Humanoid::findClosest(Humanoid enemyTeam[], int t_enemyTeamSize)
{
	int distance1 = abs(xPos - enemyTeam[0].getXPos()) + abs(yPos - enemyTeam[0].getYPos());
	int distance2 = abs(xPos - enemyTeam[1].getXPos()) + abs(yPos - enemyTeam[1].getYPos());

	int index;

	if (distance1 >= distance2)
	{
		index = 0;
	}

	else
	{
		index = 1;
	}

	return index;
}

/// <summary>
/// Moves the rabbit to its closest enemy
/// </summary>
/// <param name="t_index">The index of the closest enemy</param>
/// <param name="enemyTeam">the team with the enemies</param>
void Humanoid::moveToClosestTarget(int t_index, Humanoid enemyTeam[])
{
	for (int i{ 0 }; i < speed; i++)
	{
		if (enemyTeam[t_index].getXPos() > xPos)
		{
			xPos++;
		}

		else if (enemyTeam[t_index].getXPos() < xPos)
		{
			xPos--;
		}

		else if (enemyTeam[t_index].getYPos() > yPos)
		{
			yPos++;
		}

		else
		{
			yPos--;
		}
	}

}

/// <summary>
/// 
/// </summary>
/// <param name="enemyTeam"></param>
/// <param name="t_enemyTeamSize"></param>
void Humanoid::thoughtProcess(Humanoid enemyTeam[], int t_enemyTeamSize)
{
	bool close{ false }; // Bool that tells the code if an enemy is in movement range
	int enemyIndex{ 0 }; // which enemy the rabbit is to target

	for (int i{ 0 }; i < t_enemyTeamSize; i++)
	{
		if (withinRangeCheck(enemyTeam[i].getXPos(), enemyTeam[i].getYPos())) // checks if an enemy is in movement range
		{
			close = true;
			enemyIndex = i;
			break;
		}
	}

	if (close)
	{
		uniqueTurn(enemyTeam, enemyIndex);
	}

	else
	{
		int index = findClosest(enemyTeam, t_enemyTeamSize);
		moveToClosestTarget(index, enemyTeam);
	}
}
