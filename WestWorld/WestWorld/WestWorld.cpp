#include "Game.h"

using namespace irr;

#pragma comment (lib, "Irrlicht.lib")


//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
int main()
{
	CGame game;

	game.run();

	return 0;
}

