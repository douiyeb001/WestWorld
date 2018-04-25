#ifndef GUIBASE_H
#define GUIBASE_H

#include <irrlicht.h>
#include "currency.h"

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
	CurrencyUI(const wchar_t* pText, Currency* cManager);
	void Draw(IGUIEnvironment* gui, IVideoDriver* driver);
	const wchar_t* pText;
	const wchar_t* pScore;
private:
	
	IGUIStaticText * pStaticText;
	IGUIStaticText* pScoreText;
	Currency * cManager;

};

#endif