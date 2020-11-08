#pragma once
class Coin
{
private:
	static int wallet; // Amount of money player has

public:

	Coin();
	static void buy(int coin);
	static void addRandomAmount(int enemyDifficulty);
	static int contents();
};

