#include "Coin.h"
#include <stdlib.h> 
#include <time.h>

int Coin::wallet = 100;

/// <summary>
/// Constructor, sets up the randomiser
/// </summary>
Coin::Coin()
{
	srand(time(NULL));
}

/// <summary>
/// Takes away from bank balance
/// </summary>
/// <param name="coin">How much coin to take away</param>
void Coin::buy(int coin)
{
	wallet -= coin;
}

/// <summary>
/// Adds money into the wallet that the player looted from the enemy.
/// </summary>
/// <param name="enemyDifficulty">Used to calculate how much money the player gets after killing this enemy</param>
void Coin::addRandomAmount(int enemyDifficulty)
{
	int coin = (rand() % 10) + 1 + (enemyDifficulty * 2);
	wallet += coin;
}

/// <summary>
/// Shows the current contents of the wallet
/// </summary>
/// <returns>Contents of the wallet</returns>
int Coin::contents()
{
	return wallet;
}
