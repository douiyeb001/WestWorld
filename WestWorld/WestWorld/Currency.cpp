#include "Currency.h"

int sellValue;
int enemyValue;
const int STARTCURRENCY = 250;
const int TURRETCOST = 50;
const int OBSTACLECOST = 50;

Currency::Currency()
{
	playerCurrency = STARTCURRENCY;
}


void Currency::SellBuilding()
{
	if (true)//turret
	{
		sellValue = TURRETCOST * 0.75;

	}
	else if (true)//obstacle
	{
		sellValue = OBSTACLECOST * 0.75;
	}
	playerCurrency += sellValue;
}

bool Currency::BuildingCost(IMeshSceneNode* buildNode)
{

	if (buildNode->getID() == 15 && playerCurrency >= OBSTACLECOST)//obstacle
	{
		playerCurrency -= OBSTACLECOST;
	}
	else if (buildNode->getID() == 16 && playerCurrency >= TURRETCOST)//turret
	{
		playerCurrency -= TURRETCOST;
	}
	else
	{
		return false;
	}
}

void Currency::EnemyCurrency()
{
	playerCurrency += enemyValue;
}
