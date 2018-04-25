#ifndef GUIBASE_H
#define GUIBASE_H

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;
using namespace std;

class PlayerHealthBar {
public:
	PlayerHealthBar(IVideoDriver* driver, char const* bar);
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

class CurrencyUI {
public:
	CurrencyUI(const wchar_t* pText);
	void Draw(IGUIEnvironment* gui, IVideoDriver* driver);
	const wchar_t* pText;
private:
	
	IGUIStaticText * pStaticText;
};

#endif