#pragma once
#include <irrlicht.h>
#include "PlayerBase.h"
#include "AStar.h"
#include "IMeshSceneNode.h"
#include "IMesh.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	An opponent. </summary>
///
/// <remarks>	Rache, 23-Apr-18. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class Opponent
class Opponent : public scene::IMeshSceneNode
{
public:

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

	Opponent(scene::ISceneNode* node, scene::ISceneNode* _ground, PlayerBase* playerCore, bool obstacles[]);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Opponent(scene::IMesh* mesh, ISceneNode* parent, scene::ISceneManager* mgr, s32 id, scene::ISceneNode* _ground, std::vector<GridCell*> _path, const core::vector3df& position, const core::vector3df& rotation, const core::vector3df& scale);
	~Opponent();
	/// <summary>	The enemy. </summary>
	scene::ISceneNode* enemy;
	PlayerBase* target;
	/// <summary>	True to active. </summary>
	bool active;
	/// <summary>	The speed. </summary>
	float speed;
	/// <summary>	The ground. </summary>
	scene::ISceneNode* ground;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Query if this object collides with the given ground. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="ground">	[in,out] If non-null, the ground. </param>
	///
	/// <returns>	True if it succeeds, false if it fails. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	bool collidesWith(scene::ISceneNode* ground);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Collides with target. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="target">	Target for the. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void collidesWithTarget(PlayerBase target);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Despawns this object. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Despawn();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Damages the given target. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	///
	/// <param name="target">	Target for the. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Damage(PlayerBase target);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates this object. </summary>
	///
	/// <remarks>	Rache, 23-Apr-18. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	core::vector3df NextPathPosition(irr::core::vector3df pos, float speed);
	void Update();
	/// <summary>	The pathfinder. </summary>
	AStar pathfind;
	std::vector<GridCell*> path;
	//AStar pathfind;

	//! frame
	virtual void OnRegisterSceneNode();

	//! renders the node.
	virtual void render();

	//! returns the axis aligned bounding box of this node
	virtual const core::aabbox3d<f32>& getBoundingBox() const;

	//! returns the material based on the zero based index i. To get the amount
	//! of materials used by this scene node, use getMaterialCount().
	//! This function is needed for inserting the node into the scene hirachy on a
	//! optimal position for minimizing renderstate changes, but can also be used
	//! to directly modify the material of a scene node.
	virtual video::SMaterial& getMaterial(u32 i);

	//! returns amount of materials used by this scene node.
	virtual u32 getMaterialCount() const;

	//! Writes attributes of the scene node.
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options = 0) const;

	//! Reads attributes of the scene node.
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options = 0);

	//! Returns type of the scene node
	virtual scene::ESCENE_NODE_TYPE getType() const { return scene::ESNT_MESH; }

	//! Sets a new mesh
	virtual void setMesh(scene::IMesh* mesh);

	//! Returns the current mesh
	virtual scene::IMesh* getMesh(void) { return Mesh; }

	//! Creates shadow volume scene node as child of this node
	//! and returns a pointer to it.
	virtual scene::IShadowVolumeSceneNode* addShadowVolumeSceneNode(const scene::IMesh* shadowMesh,
		s32 id, bool zfailmethod = true, f32 infinity = 10000.0f);

	//! Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
	/* In this way it is possible to change the materials a mesh causing all mesh scene nodes
	referencing this mesh to change too. */
	virtual void setReadOnlyMaterials(bool readonly);

	//! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
	virtual bool isReadOnlyMaterials() const;
	//! Removes a child from this scene node.
	//! Implemented here, to be able to remove the shadow properly, if there is one,
	//! or to remove attached childs.
	virtual bool removeChild(ISceneNode* child);

protected:
	void copyMaterials();

	core::array<video::SMaterial> Materials;
	core::aabbox3d<f32> Box;
	video::SMaterial ReadOnlyMaterial;

	scene::IMesh* Mesh;
	scene::IShadowVolumeSceneNode* Shadow;

	s32 PassCount;
	bool ReadOnlyMaterials;
};