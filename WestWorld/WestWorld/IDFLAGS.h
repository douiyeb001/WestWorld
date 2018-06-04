#ifndef IDFLAGS_H
#define IDFLAGS_H

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Values that represent Identifier flags. </summary>
///
////////////////////////////////////////////////////////////////////////////////////////////////////

enum IDFlag
{
	// I use this ISceneNode ID to indicate a scene node that is
	// not pickable by getSceneNodeAndCollisionPointFromRay()
	spawnGround = 14,
	spawnedObstacle = 15,
	spawnedTurret = 16,
	spawnedEnemy = 17,
	ID_IsNotPickable = 0
};

#endif // !IDFLAGS_H

