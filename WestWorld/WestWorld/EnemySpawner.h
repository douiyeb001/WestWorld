// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_MESH_SCENE_NODE_H_INCLUDED__
#define __C_MESH_SCENE_NODE_H_INCLUDED__

#include "IMeshSceneNode.h"
#include "IMesh.h"
#include "AStar.h" 
#include "Opponent.h"
#include "EnemyManager.h"

namespace irr
{
	namespace scene
	{

		class EnemySpawner : public IMeshSceneNode
		{
		public:

			//! constructor
			EnemySpawner(IMesh* mesh, ISceneNode* parent, ISceneManager* mgr, s32 id,
				const core::vector3df& position,
				const core::vector3df& rotation,
				const core::vector3df& scale,
				PlayerBase* goalNode_, std::vector<bool> Obstacle,
				IMetaTriangleSelector* meta,
				EnemyManager* pEnemyManager);

			//! destructor
			virtual ~EnemySpawner();

			EnemyManager* _pEnemyManager;

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
			virtual ESCENE_NODE_TYPE getType() const { return ESNT_MESH; }

			//! Sets a new mesh
			virtual void setMesh(IMesh* mesh);

			//! Returns the current mesh
			virtual IMesh* getMesh(void) { return Mesh; }

			//! Creates shadow volume scene node as child of this node
			//! and returns a pointer to it.
			virtual IShadowVolumeSceneNode* addShadowVolumeSceneNode(const IMesh* shadowMesh,
				s32 id, bool zfailmethod = true, f32 infinity = 10000.0f);

			//! Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
			/* In this way it is possible to change the materials a mesh causing all mesh scene nodes
			referencing this mesh to change too. */
			virtual void setReadOnlyMaterials(bool readonly);

			//! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
			virtual bool isReadOnlyMaterials() const;

			//! Creates a clone of this scene node and its children.
			virtual ISceneNode* clone(ISceneNode* newParent = 0, ISceneManager* newManager = 0);

			//! Removes a child from this scene node.
			//! Implemented here, to be able to remove the shadow properly, if there is one,
			//! or to remove attached childs.
			virtual bool removeChild(ISceneNode* child);
			AStar* path;
			PlayerBase* goalNode;
			std::vector<bool> obstacle;
			void SpawnOpponent();
			//std::vector<Opponent*> enemies;  // remove this
			ISceneManager* smgr;
			IMetaTriangleSelector* meta;
			void Update();

		protected:

			void copyMaterials();

			core::array<video::SMaterial> Materials;
			core::aabbox3d<f32> Box;
			video::SMaterial ReadOnlyMaterial;

			IMesh* Mesh;
			IShadowVolumeSceneNode* Shadow;

			s32 PassCount;
			bool ReadOnlyMaterials;
			float countdownSpawn;
		};

	} // end namespace scene
} // end namespace irr

#endif