#include "Currency.h"

int sellValue;
int enemyValue = 25;
const int STARTCURRENCY = 750;
const int TURRETCOST = 200;
const int OBSTACLECOST = 25;

Currency::Currency()
{
	playerCurrency = STARTCURRENCY;
}

Currency::~Currency() {  }



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

bool Currency::CheckCurrency(int building)
{
	if (building == 1 && playerCurrency >= OBSTACLECOST)//obstacle
	{
		return true;
	}
	else if (building == 2 && playerCurrency >= TURRETCOST)//turret
	{
		return true;
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
