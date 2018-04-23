// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "IVideoDriver.h"
#include "ISceneManager.h"
#include "S3DVertex.h"
#include "ICameraSceneNode.h"
#include "IMeshCache.h"
#include "IAnimatedMesh.h"
#include "IMaterialRenderer.h"
#include "IFileSystem.h"
#include "EnemySpawner.h"
namespace irr
{
	namespace scene
	{
		//! constructor
		EnemySpawner::EnemySpawner(IMesh* mesh, ISceneNode* parent, ISceneManager* mgr, s32 id,
			const core::vector3df& position,
			const core::vector3df& rotation,
			const core::vector3df& scale,
			scene::ISceneNode* goalNode_, bool Obstacle[(World_Size / Cell_Size)*(World_Size / Cell_Size)],
			IMetaTriangleSelector* imeta,
			EnemyManager* pEnemyManager)
			: IMeshSceneNode(parent, mgr, id, position, rotation, scale), Mesh(0), Shadow(0),
			PassCount(0), ReadOnlyMaterials(false), path(new AStar(this,goalNode_,Obstacle)),goalNode(goalNode_),smgr(mgr), countdownSpawn(100.0f), _pEnemyManager(pEnemyManager)
			
		{
#ifdef _DEBUG
			setDebugName("EnemySpawner");
#endif

			setMesh(mesh);
			meta = imeta;
		}


		//! destructor
		EnemySpawner::~EnemySpawner()
		{
			if (Mesh)
				Mesh->drop();
		}


		//! frame
		void EnemySpawner::OnRegisterSceneNode()
		{
			if (IsVisible)
			{
				// because this node supports rendering of mixed mode meshes consisting of
				// transparent and solid material at the same time, we need to go through all
				// materials, check of what type they are and register this node for the right
				// render pass according to that.

				video::IVideoDriver* driver = SceneManager->getVideoDriver();

				PassCount = 0;
				int transparentCount = 0;
				int solidCount = 0;

				// count transparent and solid materials in this scene node
				if (ReadOnlyMaterials && Mesh)
				{
					// count mesh materials

					for (u32 i = 0; i<Mesh->getMeshBufferCount(); ++i)
					{
						scene::IMeshBuffer* mb = Mesh->getMeshBuffer(i);
						video::IMaterialRenderer* rnd = mb ? driver->getMaterialRenderer(mb->getMaterial().MaterialType) : 0;

						if (rnd && rnd->isTransparent())
							++transparentCount;
						else
							++solidCount;

						if (solidCount && transparentCount)
							break;
					}
				}
				else
				{
					// count copied materials

					for (u32 i = 0; i<Materials.size(); ++i)
					{
						video::IMaterialRenderer* rnd =
							driver->getMaterialRenderer(Materials[i].MaterialType);

						if (rnd && rnd->isTransparent())
							++transparentCount;
						else
							++solidCount;

						if (solidCount && transparentCount)
							break;
					}
				}

				// register according to material types counted

				if (solidCount)
					SceneManager->registerNodeForRendering(this, scene::ESNRP_SOLID);

				if (transparentCount)
					SceneManager->registerNodeForRendering(this, scene::ESNRP_TRANSPARENT);

				ISceneNode::OnRegisterSceneNode();
			}
		}


		//! renders the node.
		void EnemySpawner::render()
		{
			video::IVideoDriver* driver = SceneManager->getVideoDriver();

			if (!Mesh || !driver)
				return;

			bool isTransparentPass =
				SceneManager->getSceneNodeRenderPass() == scene::ESNRP_TRANSPARENT;

			++PassCount;

			driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
			Box = Mesh->getBoundingBox();


			// for debug purposes only:

			bool renderMeshes = true;
			video::SMaterial mat;
			if (DebugDataVisible && PassCount == 1)
			{
				// overwrite half transparency
				if (DebugDataVisible & scene::EDS_HALF_TRANSPARENCY)
				{
					for (u32 g = 0; g<Mesh->getMeshBufferCount(); ++g)
					{
						mat = Materials[g];
						mat.MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;
						driver->setMaterial(mat);
						driver->drawMeshBuffer(Mesh->getMeshBuffer(g));
					}
					renderMeshes = false;
				}
			}

			// render original meshes
			if (renderMeshes)
			{
				for (u32 i = 0; i<Mesh->getMeshBufferCount(); ++i)
				{
					scene::IMeshBuffer* mb = Mesh->getMeshBuffer(i);
					if (mb)
					{
						const video::SMaterial& material = ReadOnlyMaterials ? mb->getMaterial() : Materials[i];

						video::IMaterialRenderer* rnd = driver->getMaterialRenderer(material.MaterialType);
						bool transparent = (rnd && rnd->isTransparent());

						// only render transparent buffer if this is the transparent render pass
						// and solid only in solid pass
						if (transparent == isTransparentPass)
						{
							driver->setMaterial(material);
							driver->drawMeshBuffer(mb);
						}
					}
				}
			}

			driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

			// for debug purposes only:
			if (DebugDataVisible && PassCount == 1)
			{
				video::SMaterial m;
				m.Lighting = false;
				m.AntiAliasing = 0;
				driver->setMaterial(m);

				if (DebugDataVisible & scene::EDS_BBOX)
				{
					driver->draw3DBox(Box, video::SColor(255, 255, 255, 255));
				}
				if (DebugDataVisible & scene::EDS_BBOX_BUFFERS)
				{
					for (u32 g = 0; g<Mesh->getMeshBufferCount(); ++g)
					{
						driver->draw3DBox(
							Mesh->getMeshBuffer(g)->getBoundingBox(),
							video::SColor(255, 190, 128, 128));
					}
				}

				if (DebugDataVisible & scene::EDS_NORMALS)
				{
					// draw normals
					const f32 debugNormalLength = SceneManager->getParameters()->getAttributeAsFloat(DEBUG_NORMAL_LENGTH);
					const video::SColor debugNormalColor = SceneManager->getParameters()->getAttributeAsColor(DEBUG_NORMAL_COLOR);
					const u32 count = Mesh->getMeshBufferCount();

					for (u32 i = 0; i != count; ++i)
					{
						driver->drawMeshBufferNormals(Mesh->getMeshBuffer(i), debugNormalLength, debugNormalColor);
					}
				}

				// show mesh
				if (DebugDataVisible & scene::EDS_MESH_WIRE_OVERLAY)
				{
					m.Wireframe = true;
					driver->setMaterial(m);

					for (u32 g = 0; g<Mesh->getMeshBufferCount(); ++g)
					{
						driver->drawMeshBuffer(Mesh->getMeshBuffer(g));
					}
				}
			}
		}


		//! Removes a child from this scene node.
		//! Implemented here, to be able to remove the shadow properly, if there is one,
		//! or to remove attached childs.
		bool EnemySpawner::removeChild(ISceneNode* child)
		{

			return ISceneNode::removeChild(child);
		}


		//! returns the axis aligned bounding box of this node
		const core::aabbox3d<f32>& EnemySpawner::getBoundingBox() const
		{
			return Mesh ? Mesh->getBoundingBox() : Box;
		}


		//! returns the material based on the zero based index i. To get the amount
		//! of materials used by this scene node, use getMaterialCount().
		//! This function is needed for inserting the node into the scene hierarchy on a
		//! optimal position for minimizing renderstate changes, but can also be used
		//! to directly modify the material of a scene node.
		video::SMaterial& EnemySpawner::getMaterial(u32 i)
		{
			if (Mesh && ReadOnlyMaterials && i<Mesh->getMeshBufferCount())
			{
				ReadOnlyMaterial = Mesh->getMeshBuffer(i)->getMaterial();
				return ReadOnlyMaterial;
			}

			if (i >= Materials.size())
				return ISceneNode::getMaterial(i);

			return Materials[i];
		}


		//! returns amount of materials used by this scene node.
		u32 EnemySpawner::getMaterialCount() const
		{
			if (Mesh && ReadOnlyMaterials)
				return Mesh->getMeshBufferCount();

			return Materials.size();
		}


		//! Sets a new mesh
		void EnemySpawner::setMesh(IMesh* mesh)
		{
			if (mesh)
			{
				mesh->grab();
				if (Mesh)
					Mesh->drop();

				Mesh = mesh;
				copyMaterials();
			}
		}


		//! Creates shadow volume scene node as child of this node
		//! and returns a pointer to it.
		IShadowVolumeSceneNode* EnemySpawner::addShadowVolumeSceneNode(
			const IMesh* shadowMesh, s32 id, bool zfailmethod, f32 infinity)
		{
			if (!SceneManager->getVideoDriver()->queryFeature(video::EVDF_STENCIL_BUFFER))
				return 0;

			if (!shadowMesh)
				shadowMesh = Mesh; // if null is given, use the mesh of node

			return Shadow;
		}


		void EnemySpawner::copyMaterials()
		{
			Materials.clear();

			if (Mesh)
			{
				video::SMaterial mat;

				for (u32 i = 0; i<Mesh->getMeshBufferCount(); ++i)
				{
					IMeshBuffer* mb = Mesh->getMeshBuffer(i);
					if (mb)
						mat = mb->getMaterial();

					Materials.push_back(mat);
				}
			}
		}


		//! Writes attributes of the scene node.
		void EnemySpawner::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
		{
			IMeshSceneNode::serializeAttributes(out, options);

			if (options && (options->Flags&io::EARWF_USE_RELATIVE_PATHS) && options->Filename)
			{
				const io::path path = SceneManager->getFileSystem()->getRelativeFilename(
					SceneManager->getFileSystem()->getAbsolutePath(SceneManager->getMeshCache()->getMeshName(Mesh).getPath()),
					options->Filename);
				out->addString("Mesh", path.c_str());
			}
			else
				out->addString("Mesh", SceneManager->getMeshCache()->getMeshName(Mesh).getPath().c_str());
			out->addBool("ReadOnlyMaterials", ReadOnlyMaterials);
		}


		//! Reads attributes of the scene node.
		void EnemySpawner::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
		{
			io::path oldMeshStr = SceneManager->getMeshCache()->getMeshName(Mesh);
			io::path newMeshStr = in->getAttributeAsString("Mesh");
			ReadOnlyMaterials = in->getAttributeAsBool("ReadOnlyMaterials");

			if (newMeshStr != "" && oldMeshStr != newMeshStr)
			{
				IMesh* newMesh = 0;
				IAnimatedMesh* newAnimatedMesh = SceneManager->getMesh(newMeshStr.c_str());

				if (newAnimatedMesh)
					newMesh = newAnimatedMesh->getMesh(0);

				if (newMesh)
					setMesh(newMesh);
			}

			// optional attribute to assign the hint to the whole mesh
			if (in->existsAttribute("HardwareMappingHint") &&
				in->existsAttribute("HardwareMappingBufferType"))
			{
				scene::E_HARDWARE_MAPPING mapping = scene::EHM_NEVER;
				scene::E_BUFFER_TYPE bufferType = scene::EBT_NONE;

				core::stringc smapping = in->getAttributeAsString("HardwareMappingHint");
				if (smapping.equals_ignore_case("static"))
					mapping = scene::EHM_STATIC;
				else if (smapping.equals_ignore_case("dynamic"))
					mapping = scene::EHM_DYNAMIC;
				else if (smapping.equals_ignore_case("stream"))
					mapping = scene::EHM_STREAM;

				core::stringc sbufferType = in->getAttributeAsString("HardwareMappingBufferType");
				if (sbufferType.equals_ignore_case("vertex"))
					bufferType = scene::EBT_VERTEX;
				else if (sbufferType.equals_ignore_case("index"))
					bufferType = scene::EBT_INDEX;
				else if (sbufferType.equals_ignore_case("vertexindex"))
					bufferType = scene::EBT_VERTEX_AND_INDEX;

				IMesh* mesh = getMesh();
				if (mesh)
					mesh->setHardwareMappingHint(mapping, bufferType);
			}

			IMeshSceneNode::deserializeAttributes(in, options);
		}


		//! Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
		/* In this way it is possible to change the materials a mesh causing all mesh scene nodes
		referencing this mesh to change too. */
		void EnemySpawner::setReadOnlyMaterials(bool readonly)
		{
			ReadOnlyMaterials = readonly;
		}


		//! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
		bool EnemySpawner::isReadOnlyMaterials() const
		{
			return ReadOnlyMaterials;
		}


		//! Creates a clone of this scene node and its children.
		ISceneNode* EnemySpawner::clone(ISceneNode* newParent, ISceneManager* newManager)
		{
			if (!newParent)
				newParent = Parent;
			if (!newManager)
				newManager = SceneManager;

			EnemySpawner* nb = new EnemySpawner(Mesh, newParent,
				newManager, ID, RelativeTranslation, RelativeRotation, RelativeScale, goalNode,obstacle, meta,_pEnemyManager);

			nb->cloneMembers(this, newManager);
			nb->ReadOnlyMaterials = ReadOnlyMaterials;
			nb->Materials = Materials;
			nb->Shadow = Shadow;

			if (newParent)
				nb->drop();
			return nb;
		}

		void EnemySpawner::SpawnOpponent() {
			Opponent* spawnPoint = new Opponent(smgr->getMesh("meshes/Barrel.obj"), smgr->getRootSceneNode(), smgr,-2, smgr->getSceneNodeFromName("Ground"), path->finalPath, this->getAbsolutePosition(), core::vector3df(0, 0, 0), core::vector3df(2.0f, 2.0f, 2.0f));
			
		//	spawnPoint->setMaterialFlag(video::EMF_LIGHTING, false);
		//	spawnPoint->setMaterialTexture(0, driver->getTexture("textures/editor_defaults/default_texture.png"));
		//	spawnPoint->setPosition(position);
			scene::ITriangleSelector* selector = smgr->createTriangleSelector(spawnPoint->getMesh(), spawnPoint);
			spawnPoint->setTriangleSelector(selector);
			meta->addTriangleSelector(selector);
			
			_pEnemyManager->FillList(spawnPoint);

			selector->drop();
			//meta->drop();
			spawnPoint->drop();
			
		}

		void EnemySpawner::Update() {
			countdownSpawn -= 0.1;
			if (countdownSpawn < 0) {
				SpawnOpponent();
				countdownSpawn = 100.0f;
			}
			//for (int i = 0; i < ((enemies).size()); i++)
				//(enemies[i])->Update();
		}
	} // end namespace scene
} // end namespace irr
