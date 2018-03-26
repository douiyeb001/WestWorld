#ifndef GUIBASE_H
#define GUIBASE_H

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;
using namespace std;

class HealthBar {
public:
	HealthBar(IVideoDriver* driver, char const* bar);
	void Draw(IVideoDriver* driver);
private:
	ITexture* hpBar;
};

class Placeable {
public:
	Placeable(IVideoDriver* driver, char const* icon);
	void Draw(IVideoDriver* driver);
private:
	ITexture * placeableIcon;

};

#endif