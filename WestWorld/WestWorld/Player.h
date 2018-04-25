#ifndef PLAYER_H
#define PLAYER_H

#include <irrlicht.h>
#include "EnemyManager.h"

using namespace std;
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;


class Player
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

	Player(ISceneManager* smgr, IVideoDriver* driver, ISceneNodeAnimator* anim);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Creates a player. </summary>
	///
	/// <param name="smgr">	[in,out] If non-null, the smgr. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void CreatePlayer(ISceneManager* smgr);
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
	ISceneNode* RayCreate(ITriangleSelector* pSelector, IMetaTriangleSelector* pMeta, ICameraSceneNode*  pPlayer, ISceneManager *smgr);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Ray create. </summary>
	///
	/// <param name="pSelector">	[in,out] If non-null, the selector. </param>
	/// <param name="pMeta">		[in,out] If non-null, the meta. </param>
	/// <param name="pPlayer">  	[in,out] If non-null, the player. </param>
	/// <param name="smgr">			[in,out] If non-null, the smgr. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

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
	void OnShoot(vector3df start, vector3df end);
};
#endif // !1