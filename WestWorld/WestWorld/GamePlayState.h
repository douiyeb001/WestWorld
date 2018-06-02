

#if !defined(AFX_CGAMEPLAYSTATE_H_INCLUDED_)
#define AFX_CGAMEPLAYSTATE_H_INCLUDED_

#include "GameStates.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
// file:	CGamePlayState.h
//
// summary:	Declares the game play state class
////////////////////////////////////////////////////////////////////////////////////////////////////

class CGamePlayState : public CGameState
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Initializes this object. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Init(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Clears this object to its blank/initial state. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Clear(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Updates the given Manager. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void Update(CGameManager * pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Keyboard event. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void KeyboardEvent(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Mouse event. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void MouseEvent(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets the instance. </summary>
	///
	/// <returns>	Null if it fails, else a pointer to a CGamePlayState. </returns>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static CGamePlayState* Instance();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Destructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual ~CGamePlayState();

	/// <summary>	The selected model. </summary>
	int SelMdl;
protected:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Default constructor. </summary>
	///
	////////////////////////////////////////////////////////////////////////////////////////////////////

	CGamePlayState();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Displays the FPS described by pManager. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void DisplayFPS(CGameManager* pManager);

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Loads a map. </summary>
	///
	/// <param name="pManager">	[in,out] If non-null, the manager. </param>
	/// <param name="map">	   	The map. </param>
	////////////////////////////////////////////////////////////////////////////////////////////////////

	void LoadMap(CGameManager* pManager, const c8 *map);
	/// <summary>	The status text. </summary>
	IGUIStaticText* m_statusText;
	/// <summary>	The tmp[ 255]. </summary>
	wchar_t m_tmp[255];

	/// <summary>	The selector. </summary>
	scene::ITriangleSelector* m_Selector;

private:
	/// <summary>	singleton... </summary>
	static CGamePlayState m_PlayState;

};
#endif

