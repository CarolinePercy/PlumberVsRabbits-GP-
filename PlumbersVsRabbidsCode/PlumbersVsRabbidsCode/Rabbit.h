#pragma once
#include "Humanoid.h"
#include "Plumber.h"

class Rabbit : public Humanoid
{
public:
	Rabbit(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name);
};

