#ifndef GUIBASE_H
#define GUIBASE_H

#include <irrlicht.h>
#include "currency.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: irr
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace irr;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: core
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace core;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: gui
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace gui;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: video
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace video;

////////////////////////////////////////////////////////////////////////////////////////////////////
// namespace: std
//
// summary:	.
////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	A player health bar. </summary>
///
////////////////////////////////////////////////////////////////////////////////////////////////////

class PlayerCore {
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	/// <param name="bar">   	The bar. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	PlayerCore(IVideoDriver* driver, IGUIEnvironment* gui, char const* bar);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draws the given driver. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Draw(IVideoDriver* driver, int coreHealth);

private:
	/// <summary>	The hp bar. </summary>
	ITexture* hpBar;
	IGUIFont* font;
};

class PlayerHealth {
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	/// <param name="bar">   	The bar. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	PlayerHealth(IVideoDriver* driver, char const* hearts);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draws the given driver. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Draw(IVideoDriver* driver, int playerHealth);

private:
	/// <summary>	The hp bar. </summary>
	ITexture * hpBar;
};

class Placeable {
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Constructor. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	/// <param name="icon">  	The icon. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Placeable(IVideoDriver* driver, char const* icon);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Draws the given driver. </summary>
	///
	/// <param name="driver">	[in,out] If non-null, the driver. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void Draw(IVideoDriver* driver);

private:
	/// <summary>	The placeable icon. </summary>
	ITexture * placeableIcon;

};

class Reticle {
public:
	Reticle(IVideoDriver* driver, char const* icon);
	void Draw(IVideoDriver* driver);
private:
	ITexture * reticleSprite;
};

class HitMarker {
public:
	bool isHit;
	HitMarker(IVideoDriver* driver, char const* icon);
	void Draw(IVideoDriver* driver);
private:
	ITexture * hitMarkerSprite;
};

class GameOverScreen {

public:
	GameOverScreen(IVideoDriver* driver, char const* deadLogo);
	void Draw(IVideoDriver* driver);
	const wchar_t* deadText;


private:
	ITexture * GameOverSprite;

};

class VictoryScreen {

public:
	 VictoryScreen(IVideoDriver* driver, char const* winLogo);
	void Draw(IVideoDriver* driver);
	const wchar_t* deadText;


private:
	ITexture * VictorySprite;

};

class CurrencyUI {
public:
	CurrencyUI(IVideoDriver* driver, IGUIEnvironment* gui, char const* pCurrencyUI);
	/*void Draw(IGUIEnvironment* gui, IVideoDriver* driver);
	const wchar_t* pText;
	const wchar_t* pScore;*/
	void Draw(IGUIEnvironment* gui, IVideoDriver* driver, Currency* cManager);

private:

	/*IGUIStaticText * pStaticText;
	IGUIStaticText* pScoreText;
	Currency * cManager;*/
	ITexture* pCurrencyTexture;
	IGUIFont* font;
	//ITexture* pInfinityTexture;

};

class WaveCounterUI
{
	public:
	WaveCounterUI(IVideoDriver* pDriver, IGUIEnvironment * pGui);
	void Draw(IGUIEnvironment * pGui, IVideoDriver* pDriver,int waveNumber);
	IGUIFont* pFont;
	
private:
	IGUIStaticText * pWaveCounterText;
		
};

class WaveCounter {
public:
	WaveCounter(IVideoDriver* driver, char const* pWaveImage);
	void Draw(IVideoDriver* driver);
private:
	ITexture * pWaveImage;

};

class BuildPhaseUI {
public:
	BuildPhaseUI(IVideoDriver* driver, char const* pTurretImage, char const* pBarricadeImage);
	void Draw(IVideoDriver* driver);
	bool isBuildPhase;
	bool isBarricade;


	ITexture * pBuildImage;
	ITexture * pTurretImage;
	ITexture * pBarricadeImage;
private:
};

class Sign{
public:
	Sign(IVideoDriver* driver, char const* _pBuildSign);
	void Draw(IVideoDriver* driver);
	void ChangeImage(IVideoDriver* driver, int waveNumber);

	ITexture * pSignImage;

	//buildphase sign
	ITexture* pBuildSign;

	//wave sign
	ITexture* pWaveSign;
private:
	
	
};

class PlaceControl {
public:
	PlaceControl(IVideoDriver* driver, char const* _pPlace);
	void Draw(IVideoDriver* driver);


private:
	ITexture * pPlaceImage;
};


class DrawUI {
public:
	DrawUI(IVideoDriver* driver, IGUIEnvironment* gui);
	void Draw(IVideoDriver* driver, IGUIEnvironment* gui, Currency* cManager);

	BuildPhaseUI* pBuildPhaseUI;
	Sign* pSign;

private:
	PlayerCore * pCoreHealth;
	CurrencyUI* pCurrencyUI;
	Reticle* pReticle;
	WaveCounter* pWaveCounter;
	PlaceControl* pPlace;
	HitMarker* pHitMarker;



};

#endif