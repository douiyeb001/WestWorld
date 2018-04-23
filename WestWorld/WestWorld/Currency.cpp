#include "Currency.h"

int sellValue;
int enemyValue;
int turretCost;
int obstacleCost;

Currency::Currency(int* pcurrency)
{
	playerCurrency = pcurrency;
}

void Currency::SellBuilding()
{
	if (true)//turret
	{
		sellValue = turretCost * 0.75;

	}
	else if (true)//obstacle
	{
		sellValue = obstacleCost * 0.75;
	}
	playerCurrency += sellValue;
}

void Currency::BuildingCost()
{
	if (true)//turret
	{
		playerCurrency -= turretCost;
	}
	else if (true)//obstacle
	{
		playerCurrency -= obstacleCost;
	}
}

void Currency::EnemyCurrency()
{
	playerCurrency += enemyValue;
}
