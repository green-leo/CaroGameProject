#include "Menu.h"
#include "TextureManager.h"

Menu::Menu()
{
	font = TTF_OpenFont(font_path.c_str(), size);

	menuList[1].content = "1 Manual |2 Infomation";
	menuList[2].content = "2P";
	menuList[3].content = "1P";
	menuList[4].content = "New Game";
	menuList[5].content = "Undo";
	menuList[6].content = "Redo";
	menuList[7].content = "Quit";

	yes.content = "Yes";
	no.content = "No";
}

Menu::~Menu()
{}

void Menu::LoadMenu()
{
	LoadTex();
	LoadDest();
}

void Menu::LoadTex()
{
	for (int menuList_itr = 1; menuList_itr <= 7; ++menuList_itr)
	{
		menuList[menuList_itr].tex = TextureManager::loadFont(font, menuList[menuList_itr].content, size, color);
		SDL_QueryTexture(menuList[menuList_itr].tex, NULL, NULL, &menuList[menuList_itr].dTex.w, &menuList[menuList_itr].dTex.h);

		if (menuList_itr % 3 == 1)
		{
			menuList[menuList_itr].button = TextureManager::loadTexture("image/largeButton.png");
			menuList[menuList_itr].isActivated = TextureManager::loadTexture("image/largeisActivated.png");
		}
		else
		{
			menuList[menuList_itr].button = TextureManager::loadTexture("image/smallButton.png");
			menuList[menuList_itr].isActivated = TextureManager::loadTexture("image/smallisActivated.png");
		}

		SDL_QueryTexture(menuList[menuList_itr].button, NULL, NULL, &menuList[menuList_itr].dButton.w, &menuList[menuList_itr].dButton.h);
		menuList[menuList_itr].w = menuList[menuList_itr].dButton.w;
		menuList[menuList_itr].h = menuList[menuList_itr].dButton.h;
	}

	manualBoard = TextureManager::loadTexture("image/manualBoard.png");
	infoBoard = TextureManager::loadTexture("image/infoBoard.png");
	caroGame = TextureManager::loadTexture("image/icon.png");
	SDL_QueryTexture(infoBoard, NULL, NULL, &dBoard.w, &dBoard.h);
	dBoard.x = 629;
	dBoard.y = 15;

	player1Win = TextureManager::loadTexture("image/player1Win.png");
	player2Win = TextureManager::loadTexture("image/player2Win.png");
	youWin = TextureManager::loadTexture("image/youWin.png");
	comWin = TextureManager::loadTexture("image/comWin.png");
	tieGame = TextureManager::loadTexture("image/tieGame.png");
	SDL_QueryTexture(player1Win, NULL, NULL, &dWin.w, &dWin.h);
	dWin.x = 200;
	dWin.y = 200;
	
	quitEvent = TextureManager::loadTexture("image/quitEvent.png");
	
	yes.tex = TextureManager::loadFont(font, yes.content, 13, color);
	yes.button = TextureManager::loadTexture("image/smallButton.png");
	yes.isActivated = TextureManager::loadTexture("image/smallisActivated.png");
	SDL_QueryTexture(yes.tex, NULL, NULL, &yes.dTex.w, &yes.dTex.h);
	
	no.tex = TextureManager::loadFont(font, no.content, 13, color);
	no.button = TextureManager::loadTexture("image/smallButton.png");
	no.isActivated = TextureManager::loadTexture("image/smallisActivated.png");
	SDL_QueryTexture(no.tex, NULL, NULL, &no.dTex.w, &no.dTex.h);
	
}

void Menu::LoadDest()
{
	for (int menuList_itr = 1; menuList_itr <= 7; )
	{
		if (menuList_itr % 3 == 1)
		{
			menuList[menuList_itr].x = menuList[menuList_itr].dButton.x = 630;
			menuList[menuList_itr].y = menuList[menuList_itr].dButton.y = 350 + (menuList_itr - menuList_itr / 3 - 1) * 50;

			menuList[menuList_itr].dTex.x = menuList[menuList_itr].x + (menuList[menuList_itr].w - menuList[menuList_itr].dTex.w) / 2;
			menuList[menuList_itr].dTex.y = menuList[menuList_itr].y + (menuList[menuList_itr].h - menuList[menuList_itr].dTex.h) / 2;

			++menuList_itr;
		}
		else
		{
			menuList[menuList_itr].x = menuList[menuList_itr].dButton.x = 630;
			menuList[menuList_itr].y = menuList[menuList_itr].dButton.y = 350 + (menuList_itr - menuList_itr / 3 - 1) * 50;

			menuList[menuList_itr].dTex.x = menuList[menuList_itr].x + (menuList[menuList_itr].w - menuList[menuList_itr].dTex.w) / 2;
			menuList[menuList_itr].dTex.y = menuList[menuList_itr].y + (menuList[menuList_itr].h - menuList[menuList_itr].dTex.h) / 2;

			++menuList_itr;

			menuList[menuList_itr].x = menuList[menuList_itr].dButton.x = 760;
			menuList[menuList_itr].y = menuList[menuList_itr].dButton.y = 350 + (menuList_itr - menuList_itr / 3 - 1) * 50;

			menuList[menuList_itr].dTex.x = menuList[menuList_itr].x + (menuList[menuList_itr].w - menuList[menuList_itr].dTex.w) / 2;
			menuList[menuList_itr].dTex.y = menuList[menuList_itr].y + (menuList[menuList_itr].h - menuList[menuList_itr].dTex.h) / 2;

			++menuList_itr;
		}

	}

	yes.dButton.w = no.dButton.w = 80;
	yes.dButton.h = no.dButton.h = 30;
	yes.dButton.x = 240;
	no.dButton.x = 400;
	yes.dButton.y = no.dButton.y = 305;
	yes.dTex.x = yes.dButton.x + (yes.dButton.w - yes.dTex.w) / 2;
	yes.dTex.y = yes.dButton.y + (yes.dButton.h - yes.dTex.h) / 2;
	no.dTex.x = no.dButton.x + (no.dButton.w - no.dTex.w) / 2;
	no.dTex.y = no.dButton.y + (no.dButton.h - no.dTex.h) / 2;

}

void Menu::DrawMenu()
{
	for (int menuList_itr = 1; menuList_itr <= 7; ++menuList_itr)
	{
		TextureManager::Draw(menuList[menuList_itr].button, menuList[menuList_itr].dButton);
		TextureManager::Draw(menuList[menuList_itr].tex, menuList[menuList_itr].dTex);
	}
	
	TextureManager::Draw(caroGame, dBoard);
}

void Menu::endGame(int player)
{
	switch (player)
	{
	case 1: TextureManager::Draw(player1Win, dWin); break;
	case 2: TextureManager::Draw(player2Win, dWin); break;
	case 3: TextureManager::Draw(youWin, dWin); break;
	case 4: TextureManager::Draw(comWin, dWin); break;
	case 5: TextureManager::Draw(tieGame, dWin); break;
	}
	
	SDL_Delay(1000);
}

bool Menu::Quitevent()
{
	TextureManager::Draw(quitEvent, dWin);
	TextureManager::Draw(yes.button, yes.dButton);
	TextureManager::Draw(yes.tex, yes.dTex);
	TextureManager::Draw(no.button, no.dButton);
	TextureManager::Draw(no.tex, no.dTex);

	return !handleEvents();
}

bool Menu::handleEvents()
{
	SDL_Event e;
	int xMouse, yMouse;
	int xMdown, yMdown;
	int inYes = -1, inNo = -1;
	bool done = false;

	while (!done)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&xMouse, &yMouse);
				if (xMouse > 240 && xMouse < 320 && yMouse > 305 && yMouse < 335) //in Yes
				{
					if (inYes == 0 || inYes == -1)
					{
						TextureManager::Draw(yes.isActivated, yes.dButton);
						TextureManager::Draw(yes.tex, yes.dTex);
					}
					inYes = 1;
				}
				else
				{
					if (inYes == 1)
					{
						TextureManager::Draw(yes.button, yes.dButton);
						TextureManager::Draw(yes.tex, yes.dTex);
					}
					inYes = 0;
				}

				if (xMouse > 400 && xMouse < 480 && yMouse > 305 && yMouse < 335) //in No
				{
					if (inNo == 0 || inNo == -1)
					{
						TextureManager::Draw(no.isActivated, no.dButton);
						TextureManager::Draw(no.tex, no.dTex);
					}
					inNo = 1;
				}
				else
				{
					if (inNo == 1)
					{
						TextureManager::Draw(no.button, no.dButton);
						TextureManager::Draw(no.tex, no.dTex);
					}
					inNo = 0;
				}
			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&xMdown, &yMdown);
			}

			if (e.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&xMouse, &yMouse);

				if (xMouse > 240 && xMouse < 320 && yMouse > 305 && yMouse < 335) //in Yes
				{
					if (xMdown > 240 && xMdown < 320 && yMdown > 305 && yMdown < 335) //in Yes
						return true;
				}
				if (xMouse > 400 && xMouse < 480 && yMouse > 305 && yMouse < 335) //in No
				{
					if (xMdown > 400 && xMdown < 480 && yMdown > 305 && yMdown < 335) //in No
						return false;
				}
			}

		}
	}
}