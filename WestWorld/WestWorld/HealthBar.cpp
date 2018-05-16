//#include "HealthBar.h"
//#include <irrlicht.h>
//
//using namespace irr;
//
//
//	HealthBar::HealthBar(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id)
//		: scene::ISceneNode(parent, mgr, id)
//	{
//		Material.Wireframe = false;
//		Material.Lighting = false;
//		//Material.setTexture("scene/terrain.irr");
//
//		Vertices[0] = video::S3DVertex(0, 0, 0, 1, 1, 0,
//			video::SColor(255, 255, 255, 255), 1, 1);
//		Vertices[1] = video::S3DVertex(10, 0, 0, 1, 0, 0,
//			video::SColor(255, 255, 255, 255), 0.5, 0.5);
//		Vertices[2] = video::S3DVertex(0, 10, 0, 0, 1, 1,
//			video::SColor(255, 255, 255, 255), 1, 1);
//		Vertices[3] = video::S3DVertex(10, 10, 0, 0, 0, 1,
//			video::SColor(255, 255, 255, 255), 0.5, 0.5);
//		Vertices[4] = video::S3DVertex(20, 10, 0, 0, 1, 1,
//			video::SColor(255, 255, 255, 255), 0, 0);
//		Vertices[5] = video::S3DVertex(20, 0, 0, 0, 0, 1,
//			video::SColor(255, 255, 255, 255), 0, 0);
//
//		/*
//		The Irrlicht Engine needs to know the bounding box of a scene node.
//		It will use it for automatic culling and other things. Hence, we
//		need to create a bounding box from the 4 vertices we use.
//		If you do not want the engine to use the box for automatic culling,
//		and/or don't want to create the box, you could also call
//		irr::scene::ISceneNode::setAutomaticCulling() with irr::scene::EAC_OFF.
//		*/
//		Box.reset(Vertices[0].Pos);
//		for (s32 i = 1; i<6; ++i)
//			Box.addInternalPoint(Vertices[i].Pos);
//	}
//
//	/*
//	Before it is drawn, the irr::scene::ISceneNode::OnRegisterSceneNode()
//	method of every scene node in the scene is called by the scene manager.
//	If the scene node wishes to draw itself, it may register itself in the
//	scene manager to be drawn. This is necessary to tell the scene manager
//	when it should call irr::scene::ISceneNode::render(). For
//	example, normal scene nodes render their content one after another,
//	while stencil buffer shadows would like to be drawn after all other
//	scene nodes. And camera or light scene nodes need to be rendered before
//	all other scene nodes (if at all). So here we simply register the
//	scene node to render normally. If we would like to let it be rendered
//	like cameras or light, we would have to call
//	SceneManager->registerNodeForRendering(this, SNRT_LIGHT_AND_CAMERA);
//	After this, we call the actual
//	irr::scene::ISceneNode::OnRegisterSceneNode() method of the base class,
//	which simply lets also all the child scene nodes of this node register
//	themselves.
//	*/
//	 void HealthBar::OnRegisterSceneNode()
//	{
//		if (IsVisible)
//			SceneManager->registerNodeForRendering(this);
//
//		ISceneNode::OnRegisterSceneNode();
//	}
//
//	/*
//	In the render() method most of the interesting stuff happens: The
//	Scene node renders itself. We override this method and draw the
//	tetraeder.
//	*/
//	 void HealthBar::render()
//	{
//		u16 indices[] = { 0,1,2, 2,1,3, 1,4,3, 1,5,4 };
//		video::IVideoDriver* driver = SceneManager->getVideoDriver();
//
//		driver->setMaterial(Material);
//		driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
//		driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
//	}
//
//	/*
//	And finally we create three small additional methods.
//	irr::scene::ISceneNode::getBoundingBox() returns the bounding box of
//	this scene node, irr::scene::ISceneNode::getMaterialCount() returns the
//	amount of materials in this scene node (our tetraeder only has one
//	material), and irr::scene::ISceneNode::getMaterial() returns the
//	material at an index. Because we have only one material here, we can
//	return the only one material, assuming that no one ever calls
//	getMaterial() with an index greater than 0.
//	*/
//	 const core::aabbox3d<f32>& HealthBar::getBoundingBox() const
//	{
//		return Box;
//	}
//
//	 u32 HealthBar::getMaterialCount() const
//	{
//		return 1;
//	}
//
//	 video::SMaterial& HealthBar::getMaterial(u32 i)
//	{
//		return Material;
//	}
//
//	 void HealthBar::SetHealth(int health) {
//			 Vertices[1] = video::S3DVertex(20-health*20, 0, 0, 1, 0, 0,
//				 video::SColor(255, 255, 255, 0), 0.5, 0.5);
//
//			 Vertices[3] = video::S3DVertex(20-health*20, 10, 0, 0, 0, 1,
//				 video::SColor(255, 255, 255, 0), 0.5, 0.5);
//	 }
