#pragma once
#include <irrlicht.h>
#include "PlayerBase.h"
#include "AStar.h"
#include "IMeshSceneNode.h"
#include "IMesh.h"

class EnemyManager;

using namespace irr;
using namespace scene;
using namespace core;
using namespace video;

////////////////////////////////////////////////////////////////////////////////////////////////////
// file: Opponent.h
//
// summary:	Opponent class that inherits from IMeshSceneNode so it always has a represented node
////////////////////////////////////////////////////////////////////////////////////////////////////

class Opponent : public IMeshSceneNode {
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor </summary>
	///
	/// <param name="mesh">		[in,out] If non-null, the mesh. </param>
	/// <param name="parent">	[in,out] If non-null, the parent. </param>
	/// <param name="mgr">		[in,out] If non-null, mgr. </param>
	/// <param name="id">		[in,out] If non-null, id. </param>
	/// <param name="_ground">	[in,out] If non-null, the ground. </param>
	/// <param name="_path">	[in,out] If non-null, the path. </param>
	/// <param name="position">	[in,out] If non-null, the position. </param>
	/// <param name="rotation">	[in,out] If non-null, the rotation. </param>
	/// <param name="scale">	[in,out] If non-null, the scale. </param>
	/// <param name="_target">	[in,out] If non-null, the target. </param>
	/// <param name="_enemyManager">	[in,out] If non-null, the enemy manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	Opponent(IMesh* mesh, ISceneNode* parent, ISceneManager* mgr, s32 id, ISceneNode* _ground, std::vector<GridCell*> _path, 
		const vector3df& position, const vector3df& rotation, const vector3df& scale, PlayerBase* _target, EnemyManager* _enemyManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	~Opponent();

	/// <summary>	The speed at which the enemy moves. </summary>
	float speed;
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	If the enemy will explode or nit </summary>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	bool isExploding;
	/// <summary>	The scale of the enemy. </summary>
	float scale;

	/// <summary>	The enemy manager </summary>
	EnemyManager* enemyManager;

	/// <summary>	Despawns the enemy from the scene. </summary>
	void Despawn();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Checks the next path position. </summary>
	///
	/// <param name="pos">	The current position. </param>
	/// <param name="_speed"> 	The speed of the opponent. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	core::vector3df NextPathPosition(vector3df pos, float speed);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	The update function of the enemy. </summary>
	///
	/// <remarks> Moves the enemy along its path. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update(int deltaTime);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Change paths. </summary>
	///
	/// <param name="newPath">	The new path of the enemy. </param>
	/// <param name="changedCell"> 	The cell the enemy changed to. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void ChangePath(std::vector<GridCell*> newPath, GridCell* changedCell);
	/// <summary>	The path for the enemy to follow. </summary>
	std::vector<GridCell*> Path;
	/// <summary>	The path that the enemy follows gets updated. </summary>
	std::vector<GridCell*> UpdatedPath;
	/// <summary>	How far along the path the enemy is. </summary>
	int PathProgress;
	/// <summary>	Checks if the enemy need to back track or not. </summary>
	bool BackTracePath;
	/// <summary>	The start of the new path for the enemy to follow. </summary>
	int StartOfNewPath;
	/// <summary>	The target the enemy will want to move towards. In the case the player base. </summary>
	PlayerBase* Target;

	/* The following are implementations needed for the mesh scene node interface.
	   They are copied from the Irrlicht example named "CMeshSceneNode". */

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	On register scene node. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void OnRegisterSceneNode();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Render. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void render();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get bounding box. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual const aabbox3d<f32>& getBoundingBox() const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get material. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual SMaterial& getMaterial(u32 i);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get material count. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual u32 getMaterialCount() const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Serialize attributes. </summary>
	///
	/// <param name="out">	out. </param>
	/// <param name="options">	options. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options = 0) const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Deserialize attributes. </summary>
	///
	/// <param name="in">	in. </param>
	/// <param name="options">	options. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options = 0);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get type. </summary>
	///
	/// <returns> A type   </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual ESCENE_NODE_TYPE getType() const { return ESNT_MESH; }

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Deserialize attributes. </summary>
	///
	/// <param name="mesh">	 The mesh. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void setMesh(IMesh* mesh);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Get Mesh. </summary>
	///
	/// <returns> A mesh   </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual IMesh* getMesh(void) { return mesh; }


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Add shadow volume to scene model. </summary>
	///
	/// <param name="shadowMesh">	The mesh of the shadow. </param>
	/// <param name="id">	Id. </param>
	/// <param name="zfailmethod">	Zfailedmehtod. </param>
	/// <param name="infinity">	Infinity. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual IShadowVolumeSceneNode* addShadowVolumeSceneNode(const IMesh* shadowMesh,
		s32 id, bool zfailmethod = true, f32 infinity = 10000.0f);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Set read only materials </summary>
	///
	/// <param name="readonly">	Materials are set to read only. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual void setReadOnlyMaterials(bool readonly);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Is read only materials. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool isReadOnlyMaterials() const;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Remove child </summary>
	///
	/// <param name="child">	Child. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual bool removeChild(ISceneNode* child);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Damage core </summary>
	///
	/// <param name="target">	Target. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void DamageCore(PlayerBase* target);

protected:	
	/* The following are variables needed for the mesh scene node interface.
	   They are copied from the Irrlicht example named "CMeshSceneNode". */

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Copy materials. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void CopyMaterials();

	/// <summary>	Materials. </summary>
	core::array<SMaterial> materials;
	/// <summary>	Box. </summary>
	aabbox3d<f32> box;
	/// <summary>	Read only material. </summary>
	SMaterial readOnlyMaterial;
	/// <summary>	Mesh. </summary>
	IMesh* mesh;
	/// <summary>	Shadow. </summary>
	IShadowVolumeSceneNode* shadow;
	/// <summary>	Pass count. </summary>
	s32 passCount;
	/// <summary>	Boolean for the read only materials. </summary>
	bool readOnlyMaterials;
};