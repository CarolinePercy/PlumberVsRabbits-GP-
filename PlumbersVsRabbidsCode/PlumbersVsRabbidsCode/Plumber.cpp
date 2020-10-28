#include "Plumber.h"

Plumber::Plumber(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name)
{
	meleePower = 8;
	shieldPower = 8;
	health = 40;
	xPos = t_xPos;
	yPos = t_yPos;
	speed = 7;
	turnOrder = t_turnOrder;
	name = t_name;
}
