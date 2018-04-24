#include "Currency.h"

int sellValue;
int enemyValue;
int turretCost = 50;
int obstacleCost = 50;

Currency::Currency()
{
	playerCurrency = 50;
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

void Currency::BuildingCost(IMeshSceneNode* buildNode)
{

	if (buildNode->getID() == 15 && playerCurrency >= obstacleCost)//obstacle
	{
		playerCurrency -= obstacleCost;
	}
	else if (buildNode->getID() == 16 && playerCurrency >= turretCost)//turret
	{
		playerCurrency -= turretCost;
	}
	else
	{
		//message not enough currency
	}
}

void Currency::EnemyCurrency()
{
	playerCurrency += enemyValue;
}
