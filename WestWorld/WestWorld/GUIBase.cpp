#include "GUIBase.h"

PlayerHealthBar::PlayerHealthBar(IVideoDriver* driver, char const* bar) {
	hpBar = driver->getTexture(bar);
	driver->makeColorKeyTexture(hpBar, core::position2d<s32>(0, 0));
}

void PlayerHealthBar::Draw(IVideoDriver* driver) {
	driver->draw2DImage(hpBar, core::position2d<int>(0, driver->getScreenSize().Height - hpBar->getSize().Height), core::rect<int>(0, 0, hpBar->getSize().Width, hpBar->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}

Placeable::Placeable(IVideoDriver* driver, char const* icon1) {
	placeableIcon = driver->getTexture(icon1);
}

void Placeable::Draw(IVideoDriver* driver) {
	driver->draw2DImage(placeableIcon, core::position2d<int>(0, driver->getScreenSize().Height - placeableIcon->getSize().Height), core::rect<int>(0, 0, placeableIcon->getSize().Width, placeableIcon->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}

Reticle::Reticle(IVideoDriver* driver, char const* reticle) {
	reticleSprite = driver->getTexture(reticle);
}

void Reticle::Draw(IVideoDriver* driver) {
	driver->draw2DImage(reticleSprite, core::position2d<int>((driver->getScreenSize().Width - reticleSprite->getSize().Width )/2, (driver->getScreenSize().Height - reticleSprite->getSize().Height)/2), core::rect<int>(0, 0, reticleSprite->getSize().Width, reticleSprite->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw shooting reticle
}

