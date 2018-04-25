#include "GUIBase.h"
#include <stdio.h> 

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

CurrencyUI::CurrencyUI(const wchar_t* _pText, Currency* _cManager) {
	pText = _pText;
	cManager = _cManager;
	//pScore = (const wchar_t*)cManager->playerCurrency;
}

void CurrencyUI::Draw(IGUIEnvironment* gui, IVideoDriver* driver ) {
	
	pStaticText = gui->addStaticText(pText, rect<s32>(20, 30, 220, 50), false);
//	pText = (const wchar_t)cManager->playerCurrency;
		//swprintf_s(pText, L"%d", cManager->playerCurrency);
	//pScoreText = gui->addStaticText(pText, rect<s32>(70, 30, 270, 50), false);
	IGUIFont* font = gui->getBuiltInFont();
	
	//pScoreText = gui->addStaticText(pScore, rect<s32>(70, 30, 270, 50), false);
	if (font)
	{
		font->draw((L"%d", (stringc)cManager->playerCurrency),
			core::rect<s32>(70, 30, 270, 50),
			video::SColor(255, 0, 0, 0));
	}
	
}


