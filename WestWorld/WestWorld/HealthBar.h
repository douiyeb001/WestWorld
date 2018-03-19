#pragma once
#include <irrlicht.h>

using namespace irr;

class HealthBar : public scene::ISceneNode
{

	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[6];
	video::SMaterial Material;

public:
	HealthBar(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const core::aabbox3d<f32>& getBoundingBox() const;
	virtual u32 getMaterialCount() const;
	virtual video::SMaterial& getMaterial(u32 i);
	void SetHealth(int health);
};

