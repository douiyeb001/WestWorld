#pragma once
#include <irrlicht.h>
#include "PlayerBase.h"
#include "AStar.h"
#include "IMeshSceneNode.h"
#include "IMesh.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// file: Opponent.h
//
// summary:	Opponent class that inherits from IMeshSceneNode so it always has a represented node
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

class Opponent : public scene::IMeshSceneNode {
public:
	Opponent(scene::IMesh* mesh, ISceneNode* parent, scene::ISceneManager* mgr, s32 id, scene::ISceneNode* _ground, std::vector<GridCell*> _path, const core::vector3df& position, const core::vector3df& rotation, const core::vector3df& scale);
	~Opponent();

	/// <summary>	The speed at which the enemy moves. </summary>
	float speed;

	/// <summary>	Despawns the enemy from the scene. </summary>
	void Despawn();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Despawns the enemy from the scene. </summary>
	///
	/// <param name="pos">	The current position. </param>
	/// <param name="_speed"> 	The speed of the opponent. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	core::vector3df NextPathPosition(irr::core::vector3df pos, float speed);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	The update function of the enemy. </summary>
	///
	/// <remarks> Moves the enemy along its path. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	void Update();

	/// <summary>	The path for the enemy to follow. </summary>
	std::vector<GridCell*> path;

	/* The following are implementations needed for the mesh scene node interface.
	   They are copied from the Irrlicht example named "CMeshSceneNode". */
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const core::aabbox3d<f32>& getBoundingBox() const;
	virtual video::SMaterial& getMaterial(u32 i);
	virtual u32 getMaterialCount() const;
	virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options = 0) const;
	virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options = 0);
	virtual scene::ESCENE_NODE_TYPE getType() const { return scene::ESNT_MESH; }
	virtual void setMesh(scene::IMesh* mesh);
	virtual scene::IMesh* getMesh(void) { return Mesh; }
	virtual scene::IShadowVolumeSceneNode* addShadowVolumeSceneNode(const scene::IMesh* shadowMesh,
		s32 id, bool zfailmethod = true, f32 infinity = 10000.0f);
	virtual void setReadOnlyMaterials(bool readonly);
	virtual bool isReadOnlyMaterials() const;
	virtual bool removeChild(ISceneNode* child);

protected:	
	/* The following are variables needed for the mesh scene node interface.
	   They are copied from the Irrlicht example named "CMeshSceneNode". */
	void copyMaterials();
	core::array<video::SMaterial> Materials;
	core::aabbox3d<f32> Box;
	video::SMaterial ReadOnlyMaterial;
	scene::IMesh* Mesh;
	scene::IShadowVolumeSceneNode* Shadow;
	s32 PassCount;
	bool ReadOnlyMaterials;
};