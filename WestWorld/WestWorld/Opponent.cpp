#include "Opponent.h"
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
/// <param name="node">		 	[in,out] If non-null, the node. </param>
/// <param name="_ground">   	[in,out] If non-null, the ground. </param>
/// <param name="playerCore">	[in,out] If non-null, the player core. </param>
/// <param name="obstacles"> 	True to obstacles. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

Opponent::Opponent(scene::ISceneNode* node, scene::ISceneNode* _ground, PlayerBase* playerCore, bool obstacles[(World_Size / Cell_Size)*(World_Size / Cell_Size)]) 
	: enemy(node), target(playerCore), ground(_ground), active(true), speed(0.1), pathfind(AStar(enemy, (*playerCore).base, obstacles))
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Destructor. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

Opponent::~Opponent()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Query if this object collides with the given ground. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="ground">	[in,out] If non-null, the ground. </param>
///
/// <returns>	True if it succeeds, false if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

bool Opponent::collidesWith(scene::ISceneNode* ground)
{
	//temp
	ground->updateAbsolutePosition();
	enemy->updateAbsolutePosition();
	return ground->getTransformedBoundingBox().intersectsWithBox(enemy->getTransformedBoundingBox());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Collides with target. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
///
/// <param name="target">	Target for the. </param>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Opponent::collidesWithTarget(PlayerBase target)
{
	//temp
	target.base->updateAbsolutePosition();
	enemy->updateAbsolutePosition();
	if (target.base->getTransformedBoundingBox().intersectsWithBox(enemy->getTransformedBoundingBox()))
		target.Damaged(1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Despawns this object. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Opponent::Despawn() {
	active = false;
	enemy->setVisible(false);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Updates this object. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

void Opponent::Update() {
	enemy->setPosition(pathfind.NextPathPosition(enemy->getAbsolutePosition(), speed));
	collidesWithTarget(*target);

	while (collidesWith(ground))
		enemy->setPosition(enemy->getPosition() + core::vector3df(0, 0.001f, 0));
}