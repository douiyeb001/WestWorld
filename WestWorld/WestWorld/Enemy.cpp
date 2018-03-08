#include <irrlicht.h>

using namespace irr;
class Enemy {
	static scene::ISceneNode* enemy;

	static inline bool isInsidePoint(scene::ISceneNode* a, scene::ISceneNode* b)
	{
		//temp
		a->updateAbsolutePosition();
		b->updateAbsolutePosition();
		return a->getTransformedBoundingBox().isPointTotalInside(b->getPosition());
	}

	static inline bool collidesWith(scene::ISceneNode* a, scene::ISceneNode* b)
	{
		//temp
		a->updateAbsolutePosition();
		b->updateAbsolutePosition();
		return a->getTransformedBoundingBox().intersectsWithBox(b->getTransformedBoundingBox());
	}
};