#include "Opponent.h"
#include <irrlicht.h>
#include "IVideoDriver.h"
#include "ISceneManager.h"
#include "IMeshCache.h"
#include "IAnimatedMesh.h"
#include "IMaterialRenderer.h"
#include "IFileSystem.h"
#include "EnemyManager.h"

using namespace irr;
using namespace video;
using namespace scene;
using namespace core;

Opponent::Opponent(IMesh* mesh, ISceneNode* parent, ISceneManager* mgr, s32 id, ISceneNode* _ground, std::vector<GridCell*> _path, const vector3df& position, const vector3df& rotation, const vector3df& scale, PlayerBase* _target, EnemyManager* _enemyManager)
	: IMeshSceneNode(parent, mgr, 17, position, rotation, scale), mesh(0), passCount(0), Path(_path), speed(0.1), PathProgress(1), BackTracePath(false), Target(_target),isExploding(false),scale(1.0f), enemyManager(_enemyManager)
{
	setMesh(mesh);
}

Opponent::~Opponent()
{
	Path.clear();
	UpdatedPath.clear();
//	delete Shadow;
}

/*bool Opponent::CollidesWith(scene::ISceneNode* ground)
{
	//temp
	ground->updateAbsolutePosition();
	updateAbsolutePosition();
	return ground->getTransformedBoundingBox().intersectsWithBox(getTransformedBoundingBox());
}
*/

void Opponent::Despawn() {
	setVisible(false);
}

void Opponent::Update(int deltaTime) {
	core::vector3df pos = getAbsolutePosition();
	//int i = 1;

	if (isExploding) {
		setScale(core::vector3df(scale, scale, scale));
		scale += 0.01;
		if (scale > 2 && scale < 2.5) {
			setMaterialFlag(video::EMF_LIGHTING, false);
			setMaterialTexture(0, getSceneManager()->getVideoDriver()->getTexture("textures/fx/sprites/redparticle.bmp"));
			setMaterialFlag(video::EMF_ZWRITE_ENABLE, false);
			setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			
			//scene::ISceneNodeAnimator* anim = 0;

			//addAnimator(anim);
			//	anim->drop();
			//anim = getSceneManager()->createDeleteAnimator(300);
			//addAnimator(anim);
		}
			else if (scale > 3) {

				Target->Damaged(1,getSceneManager()->getVideoDriver());
			scene::ISceneNodeAnimator* anim = 0;

			addAnimator(anim);
			//	anim->drop();
			anim = getSceneManager()->createDeleteAnimator(300);
			addAnimator(anim);
			enemyManager->RemoveFromArray(this);
		}
	}
	else {

		irr::core::vector3df nextPos;

		nextPos.X = Path[Path.size() - PathProgress]->x;
		nextPos.Z = Path[Path.size() - PathProgress]->y;
		irr::core::vector3df distance = nextPos - pos;

		if (distance.getLength() < 1)
		{
			if (BackTracePath) {
				PathProgress--;
			}
			else {
				PathProgress++;
				if (PathProgress > Path.size()) {
					isExploding = true; PathProgress = Path.size();
				}
			}
		}
		if (BackTracePath && StartOfNewPath == PathProgress) {
			BackTracePath = false;
			Path = UpdatedPath;
		}
		distance.normalize();

		setPosition(pos + (speed * distance * deltaTime));
	}
	//setPosition(NextPathPosition(getAbsolutePosition(), speed));

	//while (CollidesWith(ground))
	//	setPosition(getPosition() + core::vector3df(0, 0.001f, 0));
}

irr::core::vector3df Opponent::NextPathPosition(vector3df pos, float speed)
{
	if (PathProgress > Path.size()) { isExploding = true; }

	if (isExploding){
		setScale(vector3df(scale,scale,scale));
		scale += 0.01;
		if (scale > 2) {
			Target->Damaged(1,getSceneManager()->getVideoDriver());

			setMaterialFlag(EMF_LIGHTING, false);
			setMaterialTexture(0, getSceneManager()->getVideoDriver()->getTexture("textures/fx/sprites/redparticle.bmp"));
			setMaterialFlag(EMF_ZWRITE_ENABLE, false);
			setMaterialType(EMT_TRANSPARENT_ADD_COLOR);

			//scene::ISceneNodeAnimator* anim = 0;

			//addAnimator(anim);
			//	anim->drop();
			//anim = getSceneManager()->createDeleteAnimator(300);
			//addAnimator(anim);
			delete this;
		}
		return pos;
	}

	vector3df nextPos;

	nextPos.X = Path[Path.size() - PathProgress]->x;
	nextPos.Z = Path[Path.size() - PathProgress]->y;
	vector3df distance = nextPos - pos;

	if (distance.getLength() < 1)
	{
		if (BackTracePath) {
			PathProgress--;
		}else
		PathProgress++;
	}
	if (BackTracePath && StartOfNewPath == PathProgress) {
		BackTracePath = false;
		Path = UpdatedPath;
	}
	distance.normalize();

	return (pos + (speed * distance));
}

void Opponent::ChangePath(std::vector<GridCell*> newPath, GridCell* changedCell) {
	bool passedChangedCell = false;
	//!checks if the enemy has passed the cell that changed
	//if it has passed that cell it won't do a new path calculation
	for (int i = 1; i < PathProgress;i++) {
		if (Path[Path.size() - i] == changedCell) {
			passedChangedCell = true;
		}
	}
	//! 
	if (!passedChangedCell) {
		for (int i = PathProgress - 1; i > 1; i--) {
			if (std::find(newPath.begin(), newPath.end(), Path[Path.size() - i]) != newPath.end()) {
				//pathProgress = i;
				BackTracePath = true;
				StartOfNewPath = i;
			}
		}
		UpdatedPath = newPath;
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

		IVideoDriver* driver = SceneManager->getVideoDriver();

		passCount = 0;
		int transparentCount = 0;
		int solidCount = 0;

		// count transparent and solid materials in this scene node
		if (readOnlyMaterials && mesh)
		{
			// count mesh materials

			for (u32 i = 0; i<mesh->getMeshBufferCount(); ++i)
			{
				IMeshBuffer* mb = mesh->getMeshBuffer(i);
				IMaterialRenderer* rnd = mb ? driver->getMaterialRenderer(mb->getMaterial().MaterialType) : 0;

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

			for (u32 i = 0; i<materials.size(); ++i)
			{
				IMaterialRenderer* rnd =
					driver->getMaterialRenderer(materials[i].MaterialType);

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
			SceneManager->registerNodeForRendering(this, ESNRP_SOLID);

		if (transparentCount)
			SceneManager->registerNodeForRendering(this, ESNRP_TRANSPARENT);

		ISceneNode::OnRegisterSceneNode();
	}
}


//! renders the node.
void Opponent::render()
{
	IVideoDriver* driver = SceneManager->getVideoDriver();

	if (!mesh || !driver)
		return;

	bool isTransparentPass =
		SceneManager->getSceneNodeRenderPass() == ESNRP_TRANSPARENT;

	++passCount;

	driver->setTransform(ETS_WORLD, AbsoluteTransformation);
	box = mesh->getBoundingBox();


	// for debug purposes only:

	bool renderMeshes = true;
	SMaterial mat;
	if (DebugDataVisible && passCount == 1)
	{
		// overwrite half transparency
		if (DebugDataVisible & EDS_HALF_TRANSPARENCY)
		{
			for (u32 g = 0; g<mesh->getMeshBufferCount(); ++g)
			{
				mat = materials[g];
				mat.MaterialType = EMT_TRANSPARENT_ADD_COLOR;
				driver->setMaterial(mat);
				driver->drawMeshBuffer(mesh->getMeshBuffer(g));
			}
			renderMeshes = false;
		}
	}

	// render original meshes
	if (renderMeshes)
	{
		for (u32 i = 0; i<mesh->getMeshBufferCount(); ++i)
		{
			IMeshBuffer* mb = mesh->getMeshBuffer(i);
			if (mb)
			{
				const SMaterial& material = readOnlyMaterials ? mb->getMaterial() : materials[i];

				IMaterialRenderer* rnd = driver->getMaterialRenderer(material.MaterialType);
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

	driver->setTransform(ETS_WORLD, AbsoluteTransformation);

	// for debug purposes only:
	if (DebugDataVisible && passCount == 1)
	{
		SMaterial m;
		m.Lighting = false;
		m.AntiAliasing = 0;
		driver->setMaterial(m);

		if (DebugDataVisible & EDS_BBOX)
		{
			driver->draw3DBox(box, SColor(255, 255, 255, 255));
		}
		if (DebugDataVisible & EDS_BBOX_BUFFERS)
		{
			for (u32 g = 0; g<mesh->getMeshBufferCount(); ++g)
			{
				driver->draw3DBox(
					mesh->getMeshBuffer(g)->getBoundingBox(),
					SColor(255, 190, 128, 128));
			}
		}

		if (DebugDataVisible & EDS_NORMALS)
		{
			// draw normals
			const f32 debugNormalLength = SceneManager->getParameters()->getAttributeAsFloat(DEBUG_NORMAL_LENGTH);
			const SColor debugNormalColor = SceneManager->getParameters()->getAttributeAsColor(DEBUG_NORMAL_COLOR);
			const u32 count = mesh->getMeshBufferCount();

			for (u32 i = 0; i != count; ++i)
			{
				driver->drawMeshBufferNormals(mesh->getMeshBuffer(i), debugNormalLength, debugNormalColor);
			}
		}

		// show mesh
		if (DebugDataVisible & EDS_MESH_WIRE_OVERLAY)
		{
			m.Wireframe = true;
			driver->setMaterial(m);

			for (u32 g = 0; g<mesh->getMeshBufferCount(); ++g)
			{
				driver->drawMeshBuffer(mesh->getMeshBuffer(g));
			}
		}
	}
}


//! Removes a child from this scene node.
//! Implemented here, to be able to remove the shadow properly, if there is one,
//! or to remove attached childs.
bool Opponent::removeChild(ISceneNode* child)
{
	return ISceneNode::removeChild(child);
}


//! returns the axis aligned bounding box of this node
const aabbox3d<f32>& Opponent::getBoundingBox() const
{
	return mesh ? mesh->getBoundingBox() : box;
}


//! returns the material based on the zero based index i. To get the amount
//! of materials used by this scene node, use getMaterialCount().
//! This function is needed for inserting the node into the scene hierarchy on a
//! optimal position for minimizing renderstate changes, but can also be used
//! to directly modify the material of a scene node.
SMaterial& Opponent::getMaterial(u32 i)
{
	if (mesh && readOnlyMaterials && i<mesh->getMeshBufferCount())
	{
		readOnlyMaterial = mesh->getMeshBuffer(i)->getMaterial();
		return readOnlyMaterial;
	}

	if (i >= materials.size())
		return ISceneNode::getMaterial(i);

	return materials[i];
}


//! returns amount of materials used by this scene node.
u32 Opponent::getMaterialCount() const
{
	if (mesh && readOnlyMaterials)
		return mesh->getMeshBufferCount();

	return materials.size();
}


//! Sets a new mesh
void Opponent::setMesh(scene::IMesh* mesh)
{
	if (mesh)
	{
		mesh = mesh;
		//enemy = SceneManager->addMeshSceneNode(mesh, 0, 17);
		//
		CopyMaterials();
	}
}


//! Creates shadow volume scene node as child of this node
//! and returns a pointer to it.
IShadowVolumeSceneNode* Opponent::addShadowVolumeSceneNode(
	const scene::IMesh* shadowMesh, s32 id, bool zfailmethod, f32 infinity)
{
	if (!SceneManager->getVideoDriver()->queryFeature(video::EVDF_STENCIL_BUFFER))
		return 0;

	if (!shadowMesh)
		shadowMesh = mesh; // if null is given, use the mesh of node

	return shadow;
}


void Opponent::CopyMaterials()
{
	materials.clear();

	if (mesh)
	{
		video::SMaterial mat;

		for (u32 i = 0; i<mesh->getMeshBufferCount(); ++i)
		{
			scene::IMeshBuffer* mb = mesh->getMeshBuffer(i);
			if (mb)
				mat = mb->getMaterial();

			materials.push_back(mat);
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
			SceneManager->getFileSystem()->getAbsolutePath(SceneManager->getMeshCache()->getMeshName(mesh).getPath()),
			options->Filename);
		out->addString("Mesh", path.c_str());
	}
	else
		out->addString("Mesh", SceneManager->getMeshCache()->getMeshName(mesh).getPath().c_str());
	out->addBool("ReadOnlyMaterials", readOnlyMaterials);
}


//! Reads attributes of the scene node.
void Opponent::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	io::path oldMeshStr = SceneManager->getMeshCache()->getMeshName(mesh);
	io::path newMeshStr = in->getAttributeAsString("Mesh");
	readOnlyMaterials = in->getAttributeAsBool("ReadOnlyMaterials");

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
	readOnlyMaterials = readonly;
}


//! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
bool Opponent::isReadOnlyMaterials() const
{
	return readOnlyMaterials;
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