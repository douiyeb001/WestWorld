#ifndef CURRENCY_H
#define CURRENCY_H

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace std;
using namespace core;


/*
This class manages the currency of the player in one central place so that you can easily modify it without searching the methods.
Every method in this class will effect the currency of the player
*/
class Currency
{
public:
	Currency();
	void SellBuilding();
	void BuildingCost(IMeshSceneNode* buildNode);
	void EnemyCurrency();
	bool CheckCurrency();

	short int playerCurrency;

private:	
	
};

#endif

