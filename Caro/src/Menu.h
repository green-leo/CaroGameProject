#pragma once
#include "Game.h"
#include <string>

class Menu
{
public:
	Menu();
	~Menu();
	
	void LoadMenu();
	void LoadTex();
	void LoadDest();

	void DrawMenu();

	void endGame(int player);

	bool Quitevent();
	bool handleEvents();

	typedef struct Button
	{
		string content;
		SDL_Texture* tex;
		SDL_Rect dTex;
		SDL_Texture* button;
		SDL_Texture* isActivated;
		SDL_Rect dButton;
		int x, y, w, h;
	} Button;

	Button menuList[10];
	int boardStatus = -1;
	SDL_Texture* infoBoard;
	SDL_Texture* manualBoard;
	SDL_Texture* caroGame;
	SDL_Rect dBoard;

private:

	SDL_Color color = { 0,0,0,0 };
	int size = 22;
	string font_path = "image/timesbd.ttf";
	TTF_Font *font;

	SDL_Texture* player1Win;
	SDL_Texture* player2Win;
	SDL_Texture* youWin;
	SDL_Texture* comWin;
	SDL_Texture* tieGame;
	SDL_Rect dWin;

	SDL_Texture* quitEvent;
	Button yes;
	Button no;

	//1 Manual|Infomation
	//2 Button onePlayer;
	//3 Button twoPlayer;
	//4 Button newGame;
	//5 Button undo;
	//6 Button redo
	//7 Button quit;

	
};