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
/// Returns the power of the character's attack, used for the other character's defend function
/// </summary>
/// <returns>The power of the attack</returns>
int Humanoid::attack()
{
	return meleePower;
}

void Humanoid::ability()
{
	std::cout << "Basic humanoids have no abilities." << std::endl;
}

/// <summary>
/// Calculates the amount of health the character would lose, given the damage the attacker did, and the strength of their defence.
/// </summary>
/// <param name="t_damage">The damage done by the attacker</param>
void Humanoid::defend(int t_damage)
{
	int finalDamage = t_damage - shieldPower;

	if (finalDamage > 0)
	{
		health -= finalDamage;
	}

	if (health <= 0)
	{
		std::cout << name << " has fallen!" << std::endl;
	}
}
