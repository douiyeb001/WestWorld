#include "SpriteAnimation.h"
#include <string>

using namespace std;


SpriteAnimation::SpriteAnimation(IrrlichtDevice* device, IVideoDriver* driver)
{
	timer = new Timer(device);
	currentFrame = 0;
	isPlaying = false;

	for (int i = 0; i < 7; i++){
		std::string suffix = std::to_string(i+1);
		std::string path = "media/coinSprites/coin0" + suffix + ".png";
		char const * test = path.c_str();
		coin[i] = driver->getTexture(test);
	}
}


SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::DrawAnim(IVideoDriver* driver) {
	if (!isPlaying) return;

	driver->draw2DImage(coin[currentFrame], 
		core::position2d<int>(200, 550 - (currentFrame*5)),
		core::rect<int>(0, 0, coin[currentFrame]->getSize().Width, coin[currentFrame]->getSize().Height), 
		nullptr,
		SColor(255, 255, 255, 255), true); //Draw bar

	if (timer->alarm()) {
		if (currentFrame < endFrame) {
			currentFrame++;
			timer->set(animationSpeed);
		}
		else {
			isPlaying = false;
			currentFrame = 0;
		}	
	}

}

void SpriteAnimation::SetPlaying() {
	if (!isPlaying) isPlaying = true;
	timer->set(animationSpeed);
}