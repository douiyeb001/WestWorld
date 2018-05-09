#include "Currency.h"

int sellValue;
int enemyValue = 25;
const int STARTCURRENCY = 10000;
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

void Currency::BuildingCost(IMeshSceneNode* buildNode)
{

	if (buildNode->getID() == 15)//obstacle
	{
		playerCurrency -= OBSTACLECOST;
		
	}
	else if (buildNode->getID() == 16)//turret
	{
		playerCurrency -= TURRETCOST;
		
	}
}

bool Currency::CheckCurrency()
{
	if (playerCurrency >= OBSTACLECOST)//obstacle
	{
		return true;
	}
	else if (playerCurrency >= TURRETCOST)//turret
	{
		return false;
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
