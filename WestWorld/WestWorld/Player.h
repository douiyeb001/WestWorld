#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#pragma once
#include "EnemyManager.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;


class Player : public IDamagable
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the camera. </summary>
	///
	/// <returns>	Null if it fails, else the camera. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	ICameraSceneNode * getCamera();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <param name="smgr">  	[in,out] If non-null, the smgr. </param>
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	/// <param name="anim">  	[in,out] If non-null, the animation. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Player(ISceneManager* smgr, IVideoDriver* driver, ISceneNodeAnimator* anim, IMetaTriangleSelector* meta);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates a player. </summary>
	///
	/// <param name="smgr">	[in,out] If non-null, the smgr. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void CreatePlayer(ISceneManager* smgr, IMetaTriangleSelector* meta);
	//void Update();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Handles the movement. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void HandleMovement();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~Player();
	ISceneNode* RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode*  pPlayer, ISceneManager *smgr, ISceneNode* gun);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Ray create. </summary>
	///
	/// <param name="pSelector">	[in,out] If non-null, the selector. </param>
	/// <param name="pMeta">		[in,out] If non-null, the meta. </param>
	/// <param name="pPlayer">  	[in,out] If non-null, the player. </param>
	/// <param name="smgr">			[in,out] If non-null, the smgr. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Damaged(int damage);
	irr::core::vector3df GetPosition();
private:

	/// <summary>	The key map. </summary>
	SKeyMap* pKeyMap;
	/// <summary>	The camera node. </summary>
	ICameraSceneNode* cameraNode;
	/// <summary>	The driver. </summary>
	IVideoDriver* pDriver;
//	ISceneManager* pSmgr;
	/// <summary>	The ray. </summary>
	core::line3d<f32> ray;
	/// <summary>	The intersection. </summary>
	vector3df intersection;
	/// <summary>	The hit triangle. </summary>
	triangle3df  hitTriangle;
	/// <summary>	The collided object. </summary>
	ISceneNode* collidedObject;
	ISceneNodeAnimatorCollisionResponse* anim;
	void OnShoot(vector3df placeHit, ISceneManager* smgr);
};
#endif // !1