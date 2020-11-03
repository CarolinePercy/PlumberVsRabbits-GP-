#pragma once
#include <iostream>

enum class shieldStrength
{
	NONE,
	SMALL,
	MEDIUM,
	LARGE
};

enum class attackType
{
	PUNCH,
	KNIFE,
	AXE,
	GUN
};


class Humanoid
{
protected:

	int health{0}; // Characters total health
	int xPos{0}; // Characters x position on the field
	int yPos{0}; // characters y position on the field
	int speed{0}; // How far the character can move in a turn
	int turnOrder{0}; // When the character has their turn in relation to other characters
	int hitsTaken{0};
	int hitsThrown{0};

	shieldStrength currentShield = shieldStrength::NONE;

public:
	std::string name; // Identification

	// Abilities
	void move(int t_newX, int t_newY);

	// Get methods 
	int getXPos();
	int getYPos();
	int getHitsTaken();
	int getHitsThrown();
	int getHealth();
	int getTurnOrder();


	// Other Methods
	void isHit(attackType t_damageType);
	void defend(shieldStrength t_newShieldType);
	int damageCalc(int t_rawDamage);
	bool withinRangeCheck(int t_enemyXPos, int t_enemyYPos);
	int distanceCalc(int t_enemyDistance, int t_allyDistance);

	int findClosest(Humanoid enemyTeam[], int t_enemyTeamSize);
	void moveToClosestTarget(int t_index, Humanoid enemyTeam[]);

	virtual void ability(Humanoid enemy);
	virtual void uniqueTurn(Humanoid enemyTeam[], int t_enemyTeamSize);
	void thoughtProcess(Humanoid enemyTeam[], int t_enemyTeamSize);
};

