#include "MyGame\MyGame.h"

int main(int argc, char * args[]) 
{
	MyGame game;
	game.Initialize();
	game.MainLoop();
	game.Finalize();
	return 0;
}