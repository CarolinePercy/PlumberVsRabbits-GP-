#pragma once
#include "Humanoid.h"
#include "Rabbit.h"

class Plumber : public Humanoid
{
public:
	Plumber(int t_xPos, int t_yPos, int t_turnOrder, std::string t_name);
};

