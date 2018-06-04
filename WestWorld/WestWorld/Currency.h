#ifndef CURRENCY_H
#define CURRENCY_H

#include <irrlicht.h>

using namespace irr;
using namespace video;
using namespace scene;
using namespace std;
using namespace core;


/*

*/

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	This class manages the currency of the player in one central place so that you can easily modify it without searching the methods.
/// Every method in this class will effect the currency of the player </summary>
///
////////////////////////////////////////////////////////////////////////////////////////////////////

class Currency
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Currency();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~Currency();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	player gets currency after it sells a building. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void SellBuilding();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Player loses currency after a building is placed </summary>
	///
	///
	/// <param name="buildNode">	[in,out] If non-null, the build node. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void BuildingCost(IMeshSceneNode* buildNode);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Player gets currency when an enemy is destroyed. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void EnemyCurrency();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Determines If the player has enough currency to place a building. </summary>
	///
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CheckCurrency();

	/// <summary>	The player's currency. </summary>
	short int playerCurrency;

private:	
	
};

#endif

