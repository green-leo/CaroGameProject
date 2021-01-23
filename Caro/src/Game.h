#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>



using namespace std;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);
	bool running() { return isRunning; }

	void setMode();
	void onePlayerMode();
	void twoPlayerMode();

	void mouseButtonDown_setMode();
	void  mouseButtonUp_setMode();
	void keyMap_setMode();

	void handleEvents();
	
	void mouseMove_inMap();
	void mouseButtonDown_inMap();
	void mouseButtonUp_inMap();
	void keyMap();

	void mouseMove_inMenu();
	void mouseButtonDown_inMenu();
	void mouseButtonUp_inMenu();

	void restart();
	void clean();

	static SDL_Renderer *renderer;
	static int turn;

	static int xKey, yKey;

private:
	
	bool isRunning = false;
	SDL_Window *window;

	int xMouse, yMouse;
	int xMsave = 11, yMsave = 10;
	int xMdown, yMdown;
	int mMovebutton = 0;
	int mDownbutton;

	int modeNum = 0;
	//twoPlayer = 1 //menuList_itr = 2
	//onePlayer = 2 //menuList_itr = 3

	bool newGame = false;
	bool conputerTurn = false;

	int comFlag;

	SDL_Event event;
};