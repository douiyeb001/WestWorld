 #include "GUIBase.h"
#include <stdio.h> 

PlayerCore::PlayerCore(IVideoDriver* driver, IGUIEnvironment* gui, char const* bar) {
	hpBar = driver->getTexture(bar);
	font = gui->getFont("media/bigfont.png");
}

void PlayerCore::Draw(IVideoDriver* driver, int coreHealth) {
	driver->draw2DImage(hpBar, core::position2d<int>(0,0), core::rect<int>(0, 0, hpBar->getSize().Width, hpBar->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
	if (font)
	{
		font->draw((L"%d", (stringc)coreHealth),
			core::rect<s32>(1179, 65, 270, 50),
			video::SColor(255, 255, 255, 255));
	}
}

PlayerHealth::PlayerHealth(IVideoDriver* driver, char const* bar) {
	hpBar = driver->getTexture(bar);
}

void PlayerHealth::Draw(IVideoDriver* driver, int playerHealth) {

	int x = 20;
	for (int i = 0; i < playerHealth; i++)
	{
		driver->draw2DImage(hpBar, core::position2d<int>(x, 10), core::rect<int>(0, 0, hpBar->getSize().Width, hpBar->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
		x += 60;
	}

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

GameOverScreen::GameOverScreen(IVideoDriver* driver, char const* deadLogo){
	GameOverSprite = driver->getTexture(deadLogo);


}
VictoryScreen::VictoryScreen(IVideoDriver* driver, char const* victoryLogo) {
	VictorySprite = driver->getTexture(victoryLogo);


}
WaveCounterUI::WaveCounterUI(IVideoDriver* pDriver, IGUIEnvironment* pGui)
{
	pFont = pGui->getFont("media/bigfont.png");
}
void WaveCounterUI::Draw(IGUIEnvironment* pGui, IVideoDriver* pDriver, int waveNumber)
{
	
	pFont->draw((L"%d", (stringc)waveNumber),
		core::rect<s32>(1150, 180, 500, 500),
		video::SColor(255, 255, 255, 255));
}

CurrencyUI::CurrencyUI(IVideoDriver* driver, IGUIEnvironment* gui, char const* pCurrency) {
	font = gui->getFont("media/bigfont.png");
	//pScore = (const wchar_t*)cager->playerCurrency;
	pCurrencyTexture = driver->getTexture(pCurrency);
	//pInfinityTexture = driver->getTexture(pInfinity);
}

void CurrencyUI::Draw(IGUIEnvironment* gui, IVideoDriver* driver, Currency* cManager) {
	
	if (font)
	{
		font->draw((L"%d", (stringc)cManager->playerCurrency),
			core::rect<s32>(200, 640, 270, 50),
			video::SColor(255, 255, 255, 255));
	}
	driver->draw2DImage(pCurrencyTexture, 
		core::position2d<int>(0, 0), 
		core::rect<int>(0, 0, pCurrencyTexture->getSize().Width, pCurrencyTexture->getSize().Height), 
		0, 
		video::SColor(255, 255, 255, 255), true); //Draw bar
}

void GameOverScreen::Draw(IVideoDriver* driver) {

	driver->draw2DImage(GameOverSprite,
		core::position2d<int>(0, 0),
		core::rect<int>(0, 0, GameOverSprite->getSize().Width, GameOverSprite->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw game over sprite
}
void VictoryScreen::Draw(IVideoDriver* driver) {
	
		driver->draw2DImage(VictorySprite,
		core::position2d<int>(0, 0),
		core::rect<int>(0, 0, VictorySprite->getSize().Width, VictorySprite->getSize().Height),
		0,
		video::SColor(255, 255, 255, 255), true); //Draw victory screen sprite
}

WaveCounter::WaveCounter(IVideoDriver* driver, char const* bar) {
	pWaveImage = driver->getTexture(bar);
	driver->makeColorKeyTexture(pWaveImage, core::position2d<s32>(0, 0));
}

void WaveCounter::Draw(IVideoDriver* driver)
{
	driver->draw2DImage(pWaveImage, core::position2d<int>(driver->getScreenSize().Width - pWaveImage->getSize().Width + 25, 144),
	core::rect<int>(0, 0, pWaveImage->getSize().Width, pWaveImage->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}	

BuildPhaseUI::BuildPhaseUI(IVideoDriver* driver, char const* _pTurretImage, char const* _pBarricadeImage) {
	isBuildPhase = false;
	pTurretImage = driver->getTexture(_pTurretImage);
	pBarricadeImage = driver->getTexture(_pBarricadeImage);
	pBuildImage = pBarricadeImage;

}

void BuildPhaseUI::Draw(IVideoDriver* driver)
{
	driver->draw2DImage(pBuildImage, core::position2d<int>(0,0),
		core::rect<int>(0, 0, pBuildImage->getSize().Width, pBuildImage->getSize().Height), 0, video::SColor(255, 255, 255, 255), true); //Draw bar
}

PlaceControl::PlaceControl(IVideoDriver* driver, char const* _pPlace)
{
	pPlaceImage = driver->getTexture(_pPlace);
}

void PlaceControl::Draw(IVideoDriver* driver)
{
	driver->draw2DImage(pPlaceImage, core::position2d<int>(driver->getScreenSize().Width / 2 + 10, driver->getScreenSize().Height / 2 + 5),
		core::rect<int>(0, 0, pPlaceImage->getSize().Width, pPlaceImage->getSize().Height), 0, video::SColor(255, 255, 255, 255), true);
}




Sign::Sign(IVideoDriver* driver, char const* _pBuildSign)
{
	pSignImage = driver->getTexture(_pBuildSign);

}

void Sign::Draw(IVideoDriver* driver)
{
	driver->draw2DImage(pSignImage, core::position2d<int>(0, 0),
		core::rect<int>(0, 0, pSignImage->getSize().Width, pSignImage->getSize().Height), 0, video::SColor(255, 255, 255, 255), true);
}

void Sign::ChangeImage(IVideoDriver* driver, int waveNumber)
{
	switch (waveNumber)
	{
	case 1:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_1.png");
		break;
	case 2:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_2.png");
		break;
	case 3:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_3.png");
		break;
	case 4:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_4.png");
		break;
	case 5:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_5.png");
		break;
	case 6:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_6.png");
		break;
	case 7:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_7.png");
		break;
	case 8:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_8.png");
		break;
	case 9:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_9.png");
		break;
	case 10:
		pWaveSign = driver->getTexture("media/UI/WaveSign/UI_WaveSign_10.png");
		break;
	}
	pSignImage = pWaveSign;
}




DrawUI::DrawUI(IVideoDriver* driver, IGUIEnvironment* gui)
{
	pCurrencyUI = new CurrencyUI(driver, gui, "media/UI/UI_Currency.png");
	pReticle = new Reticle(driver, "media/UI/rsz_reticle.png");
	//pWaveCounter = new WaveCounter(driver, "media/UI/waveCounter (Custom).png");
	pBuildPhaseUI = new BuildPhaseUI(driver, "media/UI/UI_TurretSelected.png", "media/UI/UI_BarricadeSelected.png");
	pSign = new Sign(driver, "media/UI/BuildPhaseSign.png");
	pPlace = new PlaceControl(driver, "media/UI/UI_RMB.png");
}

void DrawUI::Draw(IVideoDriver* driver, IGUIEnvironment* gui, Currency* cManager) {
	if (pBuildPhaseUI->isBuildPhase)
	{
		pBuildPhaseUI->Draw(driver);
		pPlace->Draw(driver);
		
	}
	pCurrencyUI->Draw(gui, driver, cManager);
	pReticle->Draw(driver);
	//pWaveCounter->Draw(driver);
	pSign->Draw(driver);



}

