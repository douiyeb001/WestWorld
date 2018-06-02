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
#include "timer.h"

namespace irr
{
	namespace scene
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		// file: EnemySpawner.h
		//
		// The class which is responsible for spawning the enemies.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		class EnemySpawner : public IMeshSceneNode
		{
		public:

			////////////////////////////////////////////////////////////////////////////////////////////////////
			/// <summary>	The contructor. </summary>
			///
			/// <param name="mesh">	[in,out] If non-null, the mesh. </param>
			/// <param name="parent">	[in,out] If non-null, parent. </param>
			/// <param name="mgr">	[in,out] If non-null, the mgr. </param>
			/// <param name="id">	[in,out] If non-null, the id. </param>
			/// <param name="position">	[in,out] If non-null, the psoition. </param>
			/// <param name="rotation">	[in,out] If non-null, the rotation. </param>
			/// <param name="scale">	[in,out] If non-null, the scale. </param>
			/// <param name="goalNode">	[in,out] If non-null, the goal node. </param>
			/// <param name="Obstacle">	[in,out] If non-null, the obstacle. </param>
			/// <param name="meta">	[in,out] If non-null, the meta. </param>
			/// <param name="pEnemyManager">	[in,out] If non-null, the enemy manager. </param>
			/// <param name="pTimer">	[in,out] If non-null, the timer. </param>
			////////////////////////////////////////////////////////////////////////////////////////////////////

			EnemySpawner(IMesh* mesh, ISceneNode* parent, ISceneManager* mgr, s32 id,
				const core::vector3df& position,
				const core::vector3df& rotation,
				const core::vector3df& scale,
				PlayerBase* goalNode_, std::vector<bool> Obstacle,
				IMetaTriangleSelector* meta,
				EnemyManager* pEnemyManager, Timer* pTimer);

			/// <summary>	The destructor. </summary>
			virtual ~EnemySpawner();

			/// <summary>	The enemy Manger. </summary>
			EnemyManager* _pEnemyManager;

			/// <summary>	The timer. </summary>
			Timer* p_Timer;

			/// <summary>	Frame </summary>
			virtual void OnRegisterSceneNode();

			/// <summary>	reneders the node. </summary>
			virtual void render();

			/// <summary>	Returns the axis aligned bouding box of this node. </summary>
			virtual const core::aabbox3d<f32>& getBoundingBox() const;

			/// <summary>	Returns the material based on the zero based index i. To get the amount
			/// of materials used by this scene node, use getMaterialCount().
			/// This function is needed for inserting the node into the scene hirachy on a
			/// optimal position for minimizing renderstate changes, but can also be used
			/// to directly modify the material of a scene node. </summary>
			virtual video::SMaterial& getMaterial(u32 i);

			/// <summary>	Returns amount of materials used by this scene node. </summary>
			virtual u32 getMaterialCount() const;

			/// <summary>	Writes attributes of the scene node. </summary>
			virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options = 0) const;

			/// <summary>	Reads attributes of the scene node. </summary>
			virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options = 0);

			//! Returns type of the scene node
			/// <summary>	Returns type of the scene node. </summary>
			virtual ESCENE_NODE_TYPE getType() const { return ESNT_MESH; }

			/// <summary>	Sets a new mesh. </summary>
			virtual void setMesh(IMesh* mesh);

			/// <summary>	Returns the current mesh. </summary>
			virtual IMesh* getMesh(void) { return Mesh; }

			/// <summary>	Creates shadow volume scene node as child of this node
			/// and returns a pointer to it. </summary>
			virtual IShadowVolumeSceneNode* addShadowVolumeSceneNode(const IMesh* shadowMesh,
				s32 id, bool zfailmethod = true, f32 infinity = 10000.0f);

			/// <summary>	 Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
			/// In this way it is possible to change the materials a mesh causing all mesh scene nodes
			///referencing this mesh to change too.  </summary>
			virtual void setReadOnlyMaterials(bool readonly);

			/// <summary>	Returns if. the scene node should not copy the materials of the mesh but use them in a read only style </summary>
			virtual bool isReadOnlyMaterials() const;

			/// <summary>	Creates a clone of this scene node and it's childeren. </summary>
			virtual ISceneNode* clone(ISceneNode* newParent = 0, ISceneManager* newManager = 0);

			/// <summary>	Removes a child from this scene node.
			/// Implemented here, to be able to remove the shadow properly, if there is one,
			/// or to remove attached childs. </summary>
			virtual bool removeChild(ISceneNode* child);

			/// <summary>	The enemy path. </summary>
			AStar* path;

			/// <summary>	The base as its goal. </summary>
			PlayerBase* goalNode;

			/// <summary>	Obstacles. </summary>
			std::vector<bool> obstacle;

			/// <summary>	Spawn the enemies. </summary>
			void SpawnOpponent();

			/// <summary>	The scene manager. </summary>
			ISceneManager* smgr;

			/// <summary>	The triangle selector. </summary>
			IMetaTriangleSelector* meta;

			/// <summary>	The update. </summary>
			void Update();

			/// <summary>	A new wave with enemies. </summary>
			void NewWave(int enemies);

			/// <summary>	The amount of enemies in a wave. </summary>
			int enemiesInWave;

		protected:

			/// <summary>	Make a copy of the materials. </summary>
			void copyMaterials();

			/// <summary>	The materials. </summary>
			core::array<video::SMaterial> Materials;
			
			/// <summary>	The box. </summary>
			core::aabbox3d<f32> Box;

			/// <summary>	Material that is read only. </summary>
			video::SMaterial ReadOnlyMaterial;

			/// <summary>	Mesh. </summary>
			IMesh* Mesh;

			/// <summary>	Shadow. </summary>
			IShadowVolumeSceneNode* Shadow;

			/// <summary>	Pass count. </summary>
			s32 PassCount;

			/// <summary>	A boolean for the materials that are read only. </summary>
			bool ReadOnlyMaterials;

			/// <summary>	count down spawn. </summary>
			float countdownSpawn;

		};

	} // end namespace scene
} // end namespace irr

#endif