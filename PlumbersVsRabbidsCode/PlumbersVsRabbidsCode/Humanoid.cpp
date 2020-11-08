#include "Humanoid.h"

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

/// <summary>
/// gets the name of the current character
/// </summary>
/// <returns>the name</returns>
std::string Humanoid::getName()
{
	return name;
}

/// <summary>
/// gets the name of the character
/// </summary>
/// <returns>the characters health</returns>
int Humanoid::getHealth()
{
	return roundHealth;
}

/// <summary>
/// Sets the difficulty of the team against the player
/// </summary>
/// <param name="t_newDifficulty">the new difficulty</param>
void Humanoid::setDifficulty(int t_newDifficulty)
{
	attackAddition = 5 * t_newDifficulty;
	shieldUpgrade = 10 * t_newDifficulty;
	totalHealth += t_newDifficulty * 2;
}

/// <summary>
/// Calculates the amount of health the character would lose, given the damage the attacker did, and the strength of their defence.
/// </summary>
/// <param name="t_damage">The damage done by the attacker</param>
void Humanoid::isHit(attackType t_damageType, int extraDamage)
{
	int damage = extraDamage; 

	switch (t_damageType) // the type used increases the damage given
	{
	case attackType::PUNCH:
		damage += 10;
		break;
	case attackType::KNIFE:
		damage += 15;
		break;
	case attackType::AXE:
		damage += 20;
		break;
	case attackType::GUN:
		damage += 5;
		break;
	default:
		break;
	}

	damage = damageCalc(damage); // Calculates how much health the character will lose

	roundHealth -= damage; // takes it away from character

	// Then tells the user how much health the character has, and whether the character is alive afterwards.
	std::cout << name << " lost " << abs(damage) << " HP!" << std::endl;

	if (roundHealth <= 0) // if character has lost all health, they have died 
	{
		std::cout << name << " is dead!" << std::endl;
	}

	else
	{
		std::cout << name << " remaining HP: " << roundHealth << std::endl;
	}

	letUserRead();
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
	int baseShieldRemoval = 0;
	int damageRemoved;

	switch (currentShield) // removes damage taken if the user had put up a shield
	{
	case shieldStrength::SMALL:
		baseShieldRemoval = 10;
		break;
	case shieldStrength::MEDIUM:
		baseShieldRemoval = 20;
		break;
	case shieldStrength::LARGE:
		baseShieldRemoval = 30;
		break;
	default:
		break;
	}

	damageRemoved = baseShieldRemoval + shieldUpgrade; // adds on the shield upgrade value aswell

	t_rawDamage = t_rawDamage - damageRemoved; // takes the damage away

	if (t_rawDamage < 0) // if the damage removed is more then what was delievered, set the damage to 0, else the character will restore health
	{
		t_rawDamage = 0;
	}

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
	// gets the distance from this characters position and the enemies
	int xDistance = abs(distanceCalc(xPos, t_enemyXPos));
	int yDistance = abs(distanceCalc(yPos, t_enemyYPos));

	if (xDistance + yDistance > speed) // if within distance 
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
void Humanoid::findClosest(Humanoid* enemyTeam[], int t_enemyTeamSize)
{
	int distance1 = abs(xPos - enemyTeam[0]->getXPos()) + abs(yPos - enemyTeam[0]->getYPos());
	int distance2 = abs(xPos - enemyTeam[1]->getXPos()) + abs(yPos - enemyTeam[1]->getYPos());

	int index;

	if (distance1 <= distance2 || enemyTeam[1]->getHealth() <= 0) // If the first enemy is closer, or if the second enemy is dead, then go towards first
	{
		index = 0;
	}

	else // if the second enemy is alive and closer though, go towards enemy 2
	{
		index = 1;
	}

	moveToClosestTarget(index, enemyTeam);
	currentShield = shieldStrength::MEDIUM;

	std::cout << name << " ran to (" << xPos << ", " << yPos << ") and used a medium strength shield." << std::endl;
	letUserRead();
}

/// <summary>
/// Moves the rabbit to its closest enemy
/// </summary>
/// <param name="t_index">The index of the closest enemy</param>
/// <param name="enemyTeam">the team with the enemies</param>
void Humanoid::moveToClosestTarget(int t_index, Humanoid* enemyTeam[])
{
	for (int i{ 0 }; i < speed; i++) 
	{
		if (enemyTeam[t_index]->getXPos() > xPos)
		{
			xPos++;
		}

		else if (enemyTeam[t_index]->getXPos() < xPos)
		{
			xPos--;
		}

		else if (enemyTeam[t_index]->getYPos() > yPos)
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
/// Base function. This is ideally never called, as this is purely to be overriden.
/// </summary>
/// <param name="enemy">the enemy of this character</param>
void Humanoid::ability(Humanoid enemy)
{
	std::cout << "Base humanoids have no unique abilities." << std::endl;
}

/// <summary>
/// Base function, also never called.
/// </summary>
/// <param name="enemyTeam">The enemy team</param>
/// <param name="t_enemyTeamSize">how big the enemy team is</param>
void Humanoid::uniqueTurn(Humanoid* enemyTeam[], int t_enemyTeamSize)
{
	std::cout << "Base humanoids have no unique turns." << std::endl;
}

/// <summary>
/// Enemy AI control centre. Causes it to move and attack player's team
/// </summary>
/// <param name="enemyTeam">The enemy team of this character</param>
/// <param name="t_enemyTeamSize">the </param>
void Humanoid::thoughtProcess(Humanoid* enemyTeam[], int t_enemyTeamSize)
{
	if (roundHealth > 0)
	{
		currentShield = shieldStrength::NONE;
		std::cout << name << "'s turn!" << std::endl;
		bool close{ false }; // Bool that tells the code if an enemy is in movement range
		int enemyIndex{ 0 }; // which enemy the rabbit is to target


		for (int i{ 0 }; i < t_enemyTeamSize; i++)
		{
			if (withinRangeCheck(enemyTeam[i]->getXPos(), enemyTeam[i]->getYPos()) && enemyTeam[i]->getHealth() > 0) // checks if an enemy is in movement range
			{
				close = true;
				enemyIndex = i;
				break;
			}
		}

		if (close) // If theres an enemy thats close enough to attack, they will do so
		{
			uniqueTurn(enemyTeam, enemyIndex);
		}

		else // if not, they will move towards the closest target
		{
			findClosest(enemyTeam, t_enemyTeamSize);
		}
	}
}

/// <summary>
/// The turn of the characters on the players side
/// </summary>
/// <param name="enemyTeam">The enemy team</param>
void Humanoid::playersTurn(Humanoid* enemyTeam[])
{
	int actions = 3;
	bool moved{ false };
	bool attacked{ false };
	bool shielded{ false };
	bool healed{ false };
	char input{ ' ' };

	if (roundHealth > 0) // If the character is still alive
	{
		system("CLS");

		currentShield = shieldStrength::NONE; // resets shield. Means that the player needs to use up actions to put up the shield again

		while (actions > 0)
		{
			std::cout << name << "'s turn!\n" << std::endl;

			std::cout << "Enemys' positions:";

			if (enemyTeam[0]->getHealth() > 0) // If enemy 1 is alive, display position
			{
				std::cout << " (" << enemyTeam[0]->xPos << ", " << enemyTeam[0]->yPos << ")";
			}

			if (enemyTeam[1]->getHealth() > 0) // if enemy 2 is alive, display position
			{
				std::cout << " (" << enemyTeam[1]->xPos << ", " << enemyTeam[1]->yPos << ")\n" << std::endl;
			}
			
			std::cout << "To move, input 'm' (1 action)" << std::endl;
			std::cout << "To attack, input 'a' (1-3 actions)" << std::endl;
			std::cout << "To shield, input 's' (1-3 actions)" << std::endl;
			std::cout << "To heal, input 'h' (1 action)" << std::endl;

			std::cout << "\nYour position: (" << xPos << ", " << yPos << ")" << std::endl;
			std::cout << "Health: " << getHealth() << std::endl;
			std::cout << "How far this character can move per turn: " << speed << std::endl;

			std::cout << "\nYou have " << actions << " actions left.\n" << std::endl;

			std::cin >> input;

			while (input != 'm' && input != 'a' && input != 's' && input != 'h') // if user didnt put in valid input, ask again
			{
				errorMessage();
				std::cin >> input;
			}

			if (input == 'm') 
			{
				if (!moved) // if character hasnt moved yet
				{
					playerMoveCheck();
					actions--;
					moved = true;
				}

				else
				{
					std::cout << name << " has already moved." << std::endl;
				}
				letUserRead();
				system("CLS");
			}
			else if (input == 'a')
			{
				if (!attacked) // if the character hasnt attacked yet 
				{
					playerAttackCheck(actions, enemyTeam, attacked);
					attacked = true;
				}
				else
				{
					std::cout << name << " has already attacked." << std::endl;
				}
				letUserRead();
				system("CLS");
			}

			else if (input == 's')
			{
				if (!shielded) // if the character hasnt shielded yet 
				{
					playerShieldCheck(actions);
					shielded = true;
				}
				else
				{
					std::cout << name << " is already shielded." << std::endl;
				}
				letUserRead();
				system("CLS");
			}

			else if (input == 'h')
			{
				if (!healed && getHealth() < 40) // if the character has already healed
				{
					playerHealCheck();
					actions--;
					healed = true;
				}

				else if (getHealth() >= 40)
				{
					std::cout << name << " has full health." << std::endl;
				}
				else
				{
					std::cout << name << " is already healed." << std::endl;
				}
				letUserRead();
				system("CLS");
			}
		}
	}
	
}

/// <summary>
/// Upgrades the values when player buys it
/// </summary>
/// <param name="whatToImprove">Enum that tracks what the user bought</param>
void Humanoid::upgrade(improvement whatToImprove)
{
	switch (whatToImprove) // checks what the user decided to buy, and changes the values to match
	{
	case improvement::HEALTH:
		totalHealth += 10;
		break;
	case improvement::STRENGTH:
		attackAddition += 5;
		break;
	case improvement::ATTACK:
		shieldUpgrade += 10;
		break;
	default:
		std::cout << "Error on whats improved!!" << std::endl;
		break;
	}
}

/// <summary>
/// A message thats displayed to the user, whenever they input something the program didnt ask for
/// </summary>
void Humanoid::errorMessage()
{
	std::cout << "Please enter a valid input.\n" << std::endl;
	std::cin.clear();
	std::cin.ignore(10000, '\n');
}

/// <summary>
/// Heals the current character by 5 
/// </summary>
void Humanoid::playerHealCheck()
{
	roundHealth += 5;

	std::cout << name << " healed themselves for 5 HP.\n" << std::endl;

	letUserRead();
}

/// <summary>
/// Asks where the character should move to, checks if the character can move there, and if they can, move them to it
/// </summary>
void Humanoid::playerMoveCheck()
{
	bool correctMovement{ false };
	int xMove = -100;
	int yMove = -100;
	bool error{ true };

	std::cout << "\nPlease input the x coordinate, then hit enter," << std::endl;
	std::cout << "and then enter the y coordinate to move to." << std::endl;


	while (!correctMovement)
	{
		while (error)
		{
			std::cin >> xMove; // gets value

			if (xMove <= -100)
			{
				errorMessage();
			}

			else
			{
				error = false;
			}
		}

		error = true;

		while (error)
		{	
			std::cin >> yMove; // gets value

			if (xMove <= -100)
			{
				errorMessage();
			}

			else
			{
				error = false;
			}
		}

		correctMovement = withinRangeCheck(xMove, yMove); // checks whether the character can move to that location

		if (correctMovement)
		{
		std::cout << name << " goes to (" << xMove
		<< ", " << yMove << ")." << std::endl;

		xPos = xMove;
		yPos = yMove;
		}

		else // if user cant, display error and loop back around so user can input again
		{
			std::cout << name << " can't reach there with their speed." <<
				"Try entering a different coordinate." << std::endl;
			error = true;
		}
	}
}

/// <summary>
/// Checks if there is anyone buy the player to attack, and if there is, asks user for the strength of the attack
/// </summary>
/// <param name="actions">The amount of actions the player has left</param>
/// <param name="enemyTeam">the enemy team to attack</param>
void Humanoid::playerAttackCheck(int& actions, Humanoid* enemyTeam[], bool& t_attacked)
{
	int index = -1;
	int attackStrength = 0;
	bool error = true;

	for (int i{ 0 }; i < 2; i++) // checks if an enemy shares a position with the current character
	{
		if (xPos == enemyTeam[i]->getXPos() && yPos == enemyTeam[i]->getYPos())
		{
			index = i;
			break;
		}
	}

	if (index < 0) // if no enemies positions matched the current character's position
	{
		std::cout << "There is no one around to attack!" << std::endl;
	}

	else // If they do share a space, tell user and ask for strength
	{
		std::cout << enemyTeam[index]->name << " is within attack range. Enter a number from 1 to 3," <<
			" for the strength of the attack." << std::endl;

		while (error)
		{
				std::cin >> attackStrength;
				error = false;

			if (attackStrength > 3 || attackStrength < 1) // if user put in an invalid number
			{
				errorMessage();
				error = true;
			}

			else if (actions < attackStrength) // if the user asked for an attack that is bigger then the amount of actions the player currently has
			{
				std::cout << name << " can't attack with that, they don't have enough actions! " <<
					"Please use a smaller weapon instead." << std::endl;
				error = true;
			}
		}

		// Once the player has input a valid attack

			std::cout << name << " attacks " << enemyTeam[index]->name << " with ";

			switch (attackStrength) // displays text corresponding to their input
			{
			case 1:
				std::cout << "their fists!" << std::endl;
				actions--;
				break;

			case 2:
				std::cout << "a knife!" << std::endl;
				actions -= 2;
				break;

			case 3:
				std::cout << " an axe!" << std::endl;
				actions -= 3;
				break;

			default:
				std::cout << "an error?" << std::endl;
				break;
			}

			enemyTeam[index]->isHit((attackType)attackStrength, attackAddition); // does the damage

			if (enemyTeam[index]->getHealth() <= 0) // if enemy died, give the player random amounts of coin, increasing with the difficulty of the enemy 
			{
				coinBag.addRandomAmount(attackAddition);
				std::cout << "They dropped some coins, which you put in your wallet." << std::endl;
			}

			error = false;
			t_attacked = true;
	}
}

/// <summary>
/// Asks user how strong of the shield they want to apply to the character, and error checks it
/// </summary>
/// <param name="actions">How many actions the player has left</param>
void Humanoid::playerShieldCheck(int& actions)
{
	bool correctShield{ false };
	bool error{ true };
	int strength{ 0 };

	std::cout << "Please input a number, from 1 to 3, on how strong the shield will be." <<
		"Do note the number inputted is also the amount of actions used." << std::endl;


	while (!correctShield) // loops until the user puts on a shield that works with the character's remaining actions
	{
		while (error) // error checking
		{
			try
			{
				std::cin >> strength;
				error = false;
			}

			catch (int e)
			{
			}

			if (strength > 3 || strength < 1) // if user put in a number that does not correspond to a shield strength, error
			{
				errorMessage();
				error = true;
			}
		}

		error = true;

		if (actions >= strength) // if theres enough actions for that shield, apply it
		{
			correctShield = true;
			std::cout << name << " prepares his shield to block attacks." << std::endl;
			currentShield = (shieldStrength)strength;
			actions -= strength;
		}

		else // If user used a stronger shield then what the actions allow, error
		{
			std::cout << name << " can't use that shield because they don't have enough actions." <<
				"Please use a smaller strength shield instead." << std::endl;
		}
	}
}


/// <summary>
/// Pauses the program to allow the user to read the text displayed to them in a neat and nice manner
/// </summary>
void Humanoid::letUserRead()
{
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	std::cin.get();
}