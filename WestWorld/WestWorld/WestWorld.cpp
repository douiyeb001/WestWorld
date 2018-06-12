#include "Game.h"
#include <gtest/gtest.h>

using namespace irr;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif


//INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
int main(int argc, char* argv[])
{

	testing::InitGoogleTest(&argc, argv);
	CGame game;
	
	game.run();

	return RUN_ALL_TESTS();
	//return 0;
}

