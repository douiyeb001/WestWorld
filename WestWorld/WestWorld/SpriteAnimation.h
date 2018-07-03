#pragma once
#include "Timer.h"
#include "Irrlicht.h"

using namespace video;
using namespace gui;
using namespace scene;
using namespace irr;

class SpriteAnimation
{
public:
	SpriteAnimation(IrrlichtDevice* device, IVideoDriver* driver);
	~SpriteAnimation();
	void DrawAnim(IVideoDriver* driver);
	void SetPlaying();
private:
	ITexture * coin[7];
	bool isPlaying = false;
	Timer * timer;
	int currentFrame = 0;
	int endFrame = 6;
	int animationSpeed = 50;
};

