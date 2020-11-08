#pragma once
#include <iostream>
#include "Coin.h"

/// <summary>
/// 
/// </summary>
enum class shieldStrength
{
	NONE,
	SMALL,
	MEDIUM,
	LARGE
};

/// <summary>
/// 
/// </summary>
enum class attackType
{
	GUN,
	PUNCH,
	KNIFE,
	AXE
	
};

/// <summary>
/// 
/// </summary>
enum class improvement
{
	HEALTH,
	STRENGTH,
	ATTACK
};

class Humanoid
{
protected:

	// Variables
	int roundHealth{0}; // Characters total health

	int originalXPos{ 0 }; // Where the character spawns after each round (x Axis)
	int originalYPos{ 0 }; // Where the character spawns after each round (y Axis)
	int xPos{0}; // Characters x position on the field
	int yPos{0}; // characters y position on the field

	shieldStrength currentShield = shieldStrength::NONE; // the characters current shield

	int speed{0}; // How far the character can move in a turn
	std::string name = ""; // Identification

	int attackAddition{ 0 }; // how much damage is added on (from upgrades) 
	int shieldUpgrade{ 0 }; // How much shield damage is removed from an attack (from upgrades)
	int totalHealth{ 0 }; // how much health that the character's will reset to after each round

	// Methods 
	// Actions character can take on their turn (player controls these ones)
	void playerHealCheck();
	void playerMoveCheck();
	void playerAttackCheck(int &actions, Humanoid* enemyTeam[], bool& t_attacked);
	void playerShieldCheck(int &actions);


	// Methods that handle the maths for the game
	int damageCalc(int t_rawDamage);
	bool withinRangeCheck(int t_enemyXPos, int t_enemyYPos);
	int distanceCalc(int t_enemyDistance, int t_allyDistance);
	void findClosest(Humanoid* enemyTeam[], int t_enemyTeamSize);
	void moveToClosestTarget(int t_index, Humanoid* enemyTeam[]);


	// These are the methods that show polymorphism, as the Plumbers have a different final action compared to the rabbits
	virtual void ability(Humanoid enemy);
	virtual void uniqueTurn(Humanoid* enemyTeam[], int t_enemyTeamSize);

public:
	// Get methods 
	int getXPos();
	int getYPos();
	std::string getName();
	int getHealth();
	void setDifficulty(int t_newDifficulty);

	// Methods that are used either in game, or used from within the enemy methods (ie calling an enemy to lose damage when ally throws punch)
	void isHit(attackType t_damageType, int extraDamage);
	void thoughtProcess(Humanoid* enemyTeam[], int t_enemyTeamSize);
	void playersTurn(Humanoid* enemyTeam[]);

	void upgrade(improvement whatToImprove);

	// Methods / variables that are consistant across all humanoids. Useful for when it needs to be called from main
	static Coin coinBag;
	static void letUserRead();
	static void errorMessage();
};

