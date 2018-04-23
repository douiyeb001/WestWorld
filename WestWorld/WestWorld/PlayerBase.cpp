#include "PlayerBase.h"
#include <irrlicht.h>


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Constructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="node">	[in,out] If non-null, the node. </param>
/// <param name="mgr"> 	[in,out] If non-null, the manager. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

PlayerBase::PlayerBase(scene::ISceneNode* node, scene::ISceneManager* mgr)
{
	/// <summary>	. </summary>
	base = node;
	/// <summary>	. </summary>
	healthBar = new HealthBar(node, mgr, 666);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="parameter1">	The first parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	healthBar->setPosition(irr::core::vector3df(50, 1100, 0));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="parameter1">	The first parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	healthBar->setScale(irr::core::vector3df(20, 20, 20));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="parameter1">	The first parameter. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	healthBar->setRotation(irr::core::vector3df(0, 180, 0));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the health bar > set health(*r health) </summary>
	///
	/// <value>	. </value>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	healthBar->SetHealth(*rHealth);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

PlayerBase::~PlayerBase()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Despawns this object. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PlayerBase::Despawn() {
	//base->setVisible(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Damaged. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="damage">	The damage. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void PlayerBase::Damaged(int damage) {
	/// <summary>	Remove Health. </summary>
	*rHealth -= damage;
	if (*rHealth <= 0) {
		Despawn();
		*rHealth = 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the health bar > set health(*r health) </summary>
	///
	/// <value>	. </value>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	healthBar->SetHealth(*rHealth);
}