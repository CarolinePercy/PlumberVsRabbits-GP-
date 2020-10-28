#pragma once
#include <iostream>
class Humanoid
{
protected:

	int meleePower; // How strong the characters attacks are
	int shieldPower; // How much damage the character can block
	int health; // Characters total health
	int xPos; // Characters x position on the field
	int yPos; // characters y position on the field
	int speed; // How far the character can move in a turn
	int turnOrder; // When the character has their turn in relation to other characters
	std::string name; // Identification

public:
	void move(int t_newX, int t_newY);
	int attack();
	virtual void ability();
	void defend(int t_damage);
};

