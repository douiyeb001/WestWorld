#pragma once
#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace std;
using namespace core;

class Currency
{
public:
	Currency(int* playerCurrency);
	void SellBuilding();
	void BuildingCost();
	void EnemyCurrency();
	//int playerCurrency;

	int* playerCurrency;

private:	
};

