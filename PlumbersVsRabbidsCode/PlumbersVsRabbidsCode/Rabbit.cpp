#include "Rabbit.h"

Rabbit::Rabbit(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name)
{
	meleePower = 10;
	shieldPower = 5;
	health = 30;
	xPos = t_xPos;
	yPos = t_yPos;
	speed = 4;
	turnOrder = t_turnOrder;
	name = t_name;
}
