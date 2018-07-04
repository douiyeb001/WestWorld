#include "Opponent.h"
#include <irrlicht.h>
#include "IVideoDriver.h"
#include "ISceneManager.h"
#include "IMeshCache.h"
#include "IAnimatedMesh.h"
#include "IMaterialRenderer.h"
#include "IFileSystem.h"
#include "EnemyManager.h"
#include <irrKlang-64bit-1.6.0/include/ik_ISoundEngine.h>

using namespace irr;

Opponent::Opponent(IVideoDriver* idriver, irrklang::ISoundEngine* SoundEngine, scene::IMesh* mesh, ISceneNode* parent, scene::ISceneManager* mgr, s32 id, scene::ISceneNode* _ground, std::vector<GridCell*> _path, const core::vector3df& position, const core::vector3df& rotation, const core::vector3df& scale, IDamagable* _target, EnemyManager* _enemyManager)
	: scene::IMeshSceneNode(parent, mgr, 17, position, rotation, scale), Mesh(0), PassCount(0), path(_path), speed(0.1), pathProgress(1), backTracePath(false), target(_target),isExploding(false),scale(1.5f), enemyManager(_enemyManager), targetPos(_target->GetPosition())
{
	setMesh(mesh);
	setMaterialFlag(video::EMF_LIGHTING, false);
	setMaterialTexture(0, getSceneManager()->getVideoDriver()->getTexture("textures/Enemy_Diff.PNG"));
	health = 1;
	iSoundEngine = SoundEngine;
	smgr = mgr;
	driver = idriver;
}

Opponent::~Opponent() {
	path.clear();
	updatedPath.clear();
//	delete Shadow;
}

irr::core::vector3df Opponent::GetPosition()
{
	return GetPosition();
}

void Opponent::Despawn() {
	setVisible(false);
}

void Opponent::Update(int deltaTime) {
	core::vector3df pos = getAbsolutePosition();
	//int i = 1;

	irr::core::vector3df nextPos;
	if (isExploding) {
		explodingFX = true;
		if (explodingFX)
		{
			SpawnExplosionFX(target->GetPosition(), 10);
			explodingFX = false;
		}
		setScale(core::vector3df(scale, scale, scale));
		scale += 0.01;

		if (scale > 2 && scale < 2.5) {
			setMaterialFlag(video::EMF_LIGHTING, false);
			setMaterialTexture(0, getSceneManager()->getVideoDriver()->getTexture("textures/fx/sprites/redparticle.bmp"));
			setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
			setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			
			
		}
			else if (scale > 3) {

				if (target)
					target->Damaged(1);
			scene::ISceneNodeAnimator* anim = 0;

			addAnimator(anim);
			//	anim->drop();
			anim = getSceneManager()->createDeleteAnimator(300);
			addAnimator(anim);

			iSoundEngine->play2D("media/Sound/Enemy-Explosion.wav", false);
			enemyManager->RemoveFromArray(this);
			return;
		}
			if (target) {
				nextPos.X = target->GetPosition().X;
				nextPos.Z = target->GetPosition().Z;
			}
			else {
				return;
			}
	}
	else {
		nextPos.X = path[path.size() - pathProgress]->x;
		nextPos.Z = path[path.size() - pathProgress]->y;
	}
		irr::core::vector3df distance = nextPos - pos;

		if (distance.getLength() < Cell_Size / 2)
		{
			if (backTracePath) {
				pathProgress--;
			}
			else {
				pathProgress++;
				if (pathProgress > path.size()) {
					isExploding = true; pathProgress = path.size();
				}
			}
		}
		if (backTracePath && startOfNewPath == pathProgress) {
			backTracePath = false;
			path = updatedPath;
		}
		if (pathProgress < path.size()) {
			irr::core::vector3df offset = vector3df(path[path.size() - (pathProgress + 1)]->x, 0, path[path.size() - (pathProgress + 1)]->y) - pos;
			distance = distance.getInterpolated(offset, 0.6);
		}
		//distance.rotateXYBy(offset.getSphericalCoordinateAngles.getAs3Values.X / 10);
		//distance.interpolate(distance, offset, 0.9);
		distance.normalize();

		setPosition(pos + (speed * distance * deltaTime));
		setRotation(distance.getHorizontalAngle());
}

void Opponent::Damaged(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		isExploding = true;
	}
}


void Opponent::ChangePath(std::vector<GridCell*> newPath, GridCell* changedCell) {
	bool passedChangedCell = false;
	//!checks if the enemy has passed the cell that changed
	//if it has passed that cell it won't do a new path calculation
	for (int i = 1; i < pathProgress;i++) {
		if (path[path.size() - i] == changedCell) {
			passedChangedCell = true;
		}
	}
	//! 
	if (!passedChangedCell) {
		for (int i = pathProgress - 1; i > 1; i--) {
			if (std::find(newPath.begin(), newPath.end(), path[path.size() - i]) != newPath.end()) {
				//pathProgress = i;
				backTracePath = true;
				startOfNewPath = i;
			}
		}
		updatedPath = newPath;
	}
}
//! frame
void Opponent::OnRegisterSceneNode()
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
void Opponent::render()
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
			const f32 debugNormalLength = SceneManager->getParameters()->getAttributeAsFloat(scene::DEBUG_NORMAL_LENGTH);
			const video::SColor debugNormalColor = SceneManager->getParameters()->getAttributeAsColor(scene::DEBUG_NORMAL_COLOR);
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
bool Opponent::removeChild(scene::ISceneNode* child)
{
	return ISceneNode::removeChild(child);
}


//! returns the axis aligned bounding box of this node
const core::aabbox3d<f32>& Opponent::getBoundingBox() const
{
	return Mesh ? Mesh->getBoundingBox() : Box;
}


//! returns the material based on the zero based index i. To get the amount
//! of materials used by this scene node, use getMaterialCount().
//! This function is needed for inserting the node into the scene hierarchy on a
//! optimal position for minimizing renderstate changes, but can also be used
//! to directly modify the material of a scene node.
video::SMaterial& Opponent::getMaterial(u32 i)
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
u32 Opponent::getMaterialCount() const
{
	if (Mesh && ReadOnlyMaterials)
		return Mesh->getMeshBufferCount();

	return Materials.size();
}


//! Sets a new mesh
void Opponent::setMesh(scene::IMesh* mesh)
{
	if (mesh)
	{
		Mesh = mesh;
		//enemy = SceneManager->addMeshSceneNode(mesh, 0, 17);
		//
		copyMaterials();
	}
}


//! Creates shadow volume scene node as child of this node
//! and returns a pointer to it.
scene::IShadowVolumeSceneNode* Opponent::addShadowVolumeSceneNode(
	const scene::IMesh* shadowMesh, s32 id, bool zfailmethod, f32 infinity)
{
	if (!SceneManager->getVideoDriver()->queryFeature(video::EVDF_STENCIL_BUFFER))
		return 0;

	if (!shadowMesh)
		shadowMesh = Mesh; // if null is given, use the mesh of node

	return Shadow;
}


void Opponent::copyMaterials()
{
	Materials.clear();

	if (Mesh)
	{
		video::SMaterial mat;

		for (u32 i = 0; i<Mesh->getMeshBufferCount(); ++i)
		{
			scene::IMeshBuffer* mb = Mesh->getMeshBuffer(i);
			if (mb)
				mat = mb->getMaterial();

			Materials.push_back(mat);
		}
	}
}


//! Writes attributes of the scene node.
void Opponent::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
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
void Opponent::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	io::path oldMeshStr = SceneManager->getMeshCache()->getMeshName(Mesh);
	io::path newMeshStr = in->getAttributeAsString("Mesh");
	ReadOnlyMaterials = in->getAttributeAsBool("ReadOnlyMaterials");

	if (newMeshStr != "" && oldMeshStr != newMeshStr)
	{
		scene::IMesh* newMesh = 0;
		scene::IAnimatedMesh* newAnimatedMesh = SceneManager->getMesh(newMeshStr.c_str());

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

		scene::IMesh* mesh = getMesh();
		if (mesh)
			mesh->setHardwareMappingHint(mapping, bufferType);
	}

	IMeshSceneNode::deserializeAttributes(in, options);
}


//! Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
/* In this way it is possible to change the materials a mesh causing all mesh scene nodes
referencing this mesh to change too. */
void Opponent::setReadOnlyMaterials(bool readonly)
{
	ReadOnlyMaterials = readonly;
}


//! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
bool Opponent::isReadOnlyMaterials() const
{
	return ReadOnlyMaterials;
}

/*
//! Creates a clone of this scene node and its children.
scene::ISceneNode* Opponent::clone(scene::ISceneNode* newParent, scene::ISceneManager* newManager)
{
if (!newParent)
newParent = Parent;
if (!newManager)
newManager = SceneManager;

Opponent* nb = new Opponent(Mesh, newParent,
newManager, ID, RelativeTranslation, RelativeRotation, RelativeScale, goalNode, obstacle);

nb->cloneMembers(this, newManager);
nb->ReadOnlyMaterials = ReadOnlyMaterials;
nb->Materials = Materials;
nb->Shadow = Shadow;

if (newParent)
nb->drop();
return nb;
}*/

void Opponent::SpawnExplosionFX(core::vector3df position, int directionsAmount)
{
	for (int particleIterator = 1; particleIterator < directionsAmount + 1; particleIterator++) {
		int flipper = -1;
		flipper*-1;
		scene::IParticleSystemSceneNode* ps =
			smgr->addParticleSystemSceneNode(false);

		scene::IParticleEmitter* em = ps->createBoxEmitter(
			core::aabbox3d<f32>(-7, 0, -7, 7, 1, 7),
			core::vector3df(0, 0, 0),   // initial direction
			2, 10,                             // emit rate
			video::SColor(0, 255, 255, 255),       // darkest color
			video::SColor(0, 255, 255, 255),       // brightest color
			120, 200, 0,                         // min and max age, angle
			core::dimension2df(1.f, 1.f),         // min size
			core::dimension2df(30.f, 30.f));        // max size

		ps->setEmitter(em); // this grabs the emitter
		em->drop(); // so we can drop it here without deleting it

		IParticleAffector* paf = ps->createFadeOutParticleAffector(SColor(255, 255, 255, 255));
		//	IParticleAffector* gravAf = ps->createGravityAffector(vector3df(0,0.05,0));
		//		IParticleAffector* scaleAf = ps->createScaleParticleAffector(dimension2df(0,0));
		IParticleAffector* rotAf = ps->createRotationAffector(vector3df(particleIterator * 10 * flipper, particleIterator * 10 * flipper, particleIterator * 10 * flipper), position);

		ps->addAffector(paf); // same goes for the affector
							  //	ps->addAffector(gravAf);
							  //	ps->addAffector(scaleAf);
		ps->addAffector(rotAf);

		paf->drop();
		//	gravAf->drop();
		//	scaleAf->drop();
		rotAf->drop();

		ps->setPosition(core::vector3df(position.X, position.Y + 20, position.Z));
		ps->setRotation(vector3df((rand() % 180), (rand() % 180), (rand() % 180)));
		//ps->setScale(core::vector3df(0.1, 0.2, 0.2));
		ps->setMaterialFlag(video::EMF_LIGHTING, false);
		ps->setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
		ps->setMaterialTexture(0, driver->getTexture("media/Particle_Explosion.png"));
		ps->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

		scene::ISceneNodeAnimator* anim = 0;
		anim = smgr->createDeleteAnimator(1000);
		ps->addAnimator(anim);
	}
}