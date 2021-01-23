#include "Game.h"
#include <Windows.h>

Game *game = nullptr;

int main(int argc, char *argv[])
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	game = new Game();
	
	game->init("Caro_game", 905, 610, false);

	while (game->running())
	{
		game->setMode();
	}

	game->clean();
	return 0;
}