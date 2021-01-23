#include "Game.h"
#include "Map.h"
#include "Menu.h"
#include "TextureManager.h"

int Game::turn = -1;
int Game::xKey = 10;
int Game::yKey = 10;
SDL_Renderer* Game::renderer = nullptr;
Map* map = NULL;
Menu* menu = NULL;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
			SDL_RenderClear(renderer);

			SDL_RenderPresent(renderer);
		}

		isRunning = true;
	}

	TTF_Init();

	map = new Map();
	map->LoadMap();
	map->DrawMap();


	menu = new Menu();
	menu->LoadMenu();
	menu->DrawMenu();

}


void Game::setMode()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = menu->Quitevent();
			if (isRunning) restart();
		}
		else
		{
			//Mouse Events
			if (event.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&xMouse, &yMouse);

				if (xMouse > 5 && xMouse < 605 && yMouse > 5 && yMouse < 605) //in map
				{
					mouseMove_inMap();
				}
				else //in manual or somewhere else
				{
					map->renderEvent(4, xMsave, yMsave);

					if (xMouse > 630 && xMdown < 880 && yMouse > 350 && yMouse < 595) mouseMove_inMenu();
					else
					{
						if ((modeNum == 0 || mMovebutton != modeNum + 1) && mMovebutton != 0)
						{
							TextureManager::Draw(menu->menuList[mMovebutton].button, menu->menuList[mMovebutton].dButton);
							TextureManager::Draw(menu->menuList[mMovebutton].tex, menu->menuList[mMovebutton].dTex);
						}
						//menu->boardStatus = -1;

						mMovebutton = 0;
					}
				}
			}

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&xMdown, &yMdown);
				if (xMouse > 630 && xMdown < 880 && yMouse > 350 && yMouse < 595) mouseButtonDown_setMode();
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&xMouse, &yMouse);
				if (xMouse > 630 && xMdown < 880 && yMouse > 350 && yMouse < 595) mouseButtonUp_setMode();
			}


			//Key Events
			keyMap_setMode();
		}
	}

	if (newGame)
	{

		newGame = false;
		if (modeNum == 1) twoPlayerMode();
		else onePlayerMode();
	}

}

void Game::mouseButtonDown_setMode()
{
	for (int menuList_itr = 1; menuList_itr <= 7; ++menuList_itr)
	{
		if (xMouse > menu->menuList[menuList_itr].x && xMouse < menu->menuList[menuList_itr].x + menu->menuList[menuList_itr].w
			&& yMouse > menu->menuList[menuList_itr].y && yMouse < menu->menuList[menuList_itr].y + menu->menuList[menuList_itr].h)
		{
			mDownbutton = menuList_itr;

			return;
		}
	}
}

void Game::mouseButtonUp_setMode()
{
	for (int menuList_itr = 1; menuList_itr <= 7; ++menuList_itr)
	{
		if (xMouse > menu->menuList[menuList_itr].x && xMouse < menu->menuList[menuList_itr].x + menu->menuList[menuList_itr].w
			&& yMouse > menu->menuList[menuList_itr].y && yMouse < menu->menuList[menuList_itr].y + menu->menuList[menuList_itr].h)
		{

			if (mDownbutton == menuList_itr)
			{
				switch (menuList_itr)
				{
				case 1:
				{
					menu->boardStatus = (menu->boardStatus + 1) % 2;
					if (menu->boardStatus == 0)
					{
						TextureManager::Draw(menu->manualBoard, menu->dBoard);
					}
					else
					{
						TextureManager::Draw(menu->infoBoard, menu->dBoard);
					}
					break;
				}
				case 2:
				{
					if (modeNum == 1)
					{
						modeNum = 0;
						TextureManager::Draw(menu->menuList[2].button, menu->menuList[2].dButton);
						TextureManager::Draw(menu->menuList[2].tex, menu->menuList[2].dTex);
					}
					else
					{
						if (modeNum == 2)
						{
							TextureManager::Draw(menu->menuList[3].button, menu->menuList[3].dButton);
							TextureManager::Draw(menu->menuList[3].tex, menu->menuList[3].dTex);
						}
						modeNum = 1;
						TextureManager::Draw(menu->menuList[2].isActivated, menu->menuList[2].dButton);
						TextureManager::Draw(menu->menuList[2].tex, menu->menuList[2].dTex);
					}
					newGame = false;
					restart();
					break;
				}
				case 3:
				{
					if (modeNum == 2)
					{
						modeNum = 0;
						TextureManager::Draw(menu->menuList[3].button, menu->menuList[3].dButton);
						TextureManager::Draw(menu->menuList[3].tex, menu->menuList[3].dTex);
					}
					else
					{
						if (modeNum == 1)
						{
							TextureManager::Draw(menu->menuList[2].button, menu->menuList[2].dButton);
							TextureManager::Draw(menu->menuList[2].tex, menu->menuList[2].dTex);
						}
						modeNum = 2;
						TextureManager::Draw(menu->menuList[3].isActivated, menu->menuList[3].dButton);
						TextureManager::Draw(menu->menuList[3].tex, menu->menuList[3].dTex);
					}
					newGame = false;
					restart();
					break;
				}
				case 4:
				{
					if (modeNum != 0)
					{
						newGame = true;

						restart();
					}
					break;
				}

				case 5, 6:
				{
					break;
				}
				case 7:
				{
					isRunning = menu->Quitevent();
					if (isRunning) restart();
				}
				}
			}

			return;
		}
	}

}


void Game::keyMap_setMode()
{
	if (event.type == SDL_KEYDOWN)
	{
		int x = xKey;
		int y = yKey;

		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
		{
			if (yKey > 1) --yKey;
			break;
		}
		case SDLK_DOWN:
		{
			if (yKey < 20) ++yKey;
			break;
		}
		case SDLK_RIGHT:
		{
			if (xKey < 20) ++xKey;
			break;
		}
		case SDLK_LEFT:
		{
			if (xKey > 1) --xKey;
			break;
		}
		}

		if (x != xKey || y != yKey) map->renderEvent(4, x, y);
		map->renderEvent(2, xMouse, yMouse);
		map->renderEvent(3, xKey, yKey);
	}
}





void Game::handleEvents()
{

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = menu->Quitevent();
			if (isRunning) restart();
		}
		else
		{
			//Mouse Events
			if (event.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&xMouse, &yMouse);

				if (xMouse > 5 && xMouse < 605 && yMouse > 5 && yMouse < 605) //in map
				{
					mouseMove_inMap();
				}
				else //in manual or somewhere else
				{
					map->renderEvent(4, xMsave, yMsave);


					if (xMouse >= 630 && xMdown <= 880 && yMouse >= 350 && yMouse <= 595) mouseMove_inMenu();
					else
					{
						map->renderEvent(4, xMsave, yMsave);
						if ((modeNum == 0 || mMovebutton != modeNum + 1) && mMovebutton != 0)
						{
							TextureManager::Draw(menu->menuList[mMovebutton].button, menu->menuList[mMovebutton].dButton);
							TextureManager::Draw(menu->menuList[mMovebutton].tex, menu->menuList[mMovebutton].dTex);
						}
						mMovebutton = 0;
					}

				}

			}


			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&xMdown, &yMdown);
				if (xMdown > 5 && xMdown < 605 && yMdown > 5 && yMdown < 605) //in map
				{
					mouseButtonDown_inMap();
				}
				else //in somewhere else
				{
					if (xMouse > 630 && xMdown < 880 && yMouse > 350 && yMouse < 595) mouseButtonDown_inMenu();
				}
			}

			if (event.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&xMouse, &yMouse);

				if (xMouse > 5 && xMouse < 605 && yMouse > 5 && yMouse < 605) //in map
				{
					mouseButtonUp_inMap();
				}
				else //in somewhere else
				{
					if (xMouse > 630 && xMdown < 880 && yMouse > 350 && yMouse < 595) mouseButtonUp_inMenu();
				}
			}


			//Key Events
			keyMap();


		}

	}

}


void Game::mouseMove_inMap()
{
	xMouse = xMouse - 5;
	if (xMouse % 30 == 0) xMouse = xMouse / 30;
	else xMouse = xMouse / 30 + 1;
	yMouse = yMouse - 5;
	if (yMouse % 30 == 0) yMouse = yMouse / 30;
	else yMouse = yMouse / 30 + 1;

	if (xMsave != xMouse || yMsave != yMouse) map->renderEvent(4, xMsave, yMsave);
	map->renderEvent(3, xKey, yKey);
	map->renderEvent(2, xMouse, yMouse);

	xMsave = xMouse;
	yMsave = yMouse;
}

void Game::mouseButtonDown_inMap()
{
	xMdown -= 5;
	if (xMdown % 30 == 0) xMdown = xMdown / 30;
	else xMdown = xMdown / 30 + 1;

	yMdown -= 5;
	if (yMdown % 30 == 0) yMdown = yMdown / 30;
	else yMdown = yMdown / 30 + 1;
}

void Game::mouseButtonUp_inMap()
{
	xMouse = xMouse - 5;
	if (xMouse % 30 == 0) xMouse = xMouse / 30;
	else xMouse = xMouse / 30 + 1;
	yMouse = yMouse - 5;
	if (yMouse % 30 == 0) yMouse = yMouse / 30;
	else yMouse = yMouse / 30 + 1;


	if (xMdown == xMouse && yMdown == yMouse)
	{
		if (map->map[yMdown][xMdown] == -1)
		{
			turn = (turn + 1) % 2;
			map->Update(turn, xMdown, yMdown);

			conputerTurn = true;

		}
	}
}

void Game::keyMap()
{
	if (event.type == SDL_KEYDOWN)
	{
		int x = xKey;
		int y = yKey;

		switch (event.key.keysym.sym)
		{
		case SDLK_UP:
		{
			if (yKey > 1) --yKey;
			break;
		}
		case SDLK_DOWN:
		{
			if (yKey < 20) ++yKey;
			break;
		}
		case SDLK_RIGHT:
		{
			if (xKey < 20) ++xKey;
			break;
		}
		case SDLK_LEFT:
		{
			if (xKey > 1) --xKey;
			break;
		}
		case SDLK_SPACE:
		{

			if (map->map[yKey][xKey] == -1)
			{
				turn = (turn + 1) % 2;
				map->Update(turn, xKey, yKey);

				conputerTurn = true;
			}
			break;
		}
		}

		if (x != xKey || y != yKey) map->renderEvent(4, x, y);
		map->renderEvent(2, xMouse, yMouse);
		map->renderEvent(3, xKey, yKey);
	}
}

void Game::mouseMove_inMenu()
{
	for (int menuList_itr = 1; menuList_itr <= 7; ++menuList_itr)
	{
		if (xMouse > menu->menuList[menuList_itr].x && xMouse < menu->menuList[menuList_itr].x + menu->menuList[menuList_itr].w
			&& yMouse > menu->menuList[menuList_itr].y && yMouse < menu->menuList[menuList_itr].y + menu->menuList[menuList_itr].h)
		{
			if (menuList_itr != mMovebutton)
			{
				if (mMovebutton != 0 && (mMovebutton != modeNum + 1 || modeNum == 0))
				{
					TextureManager::Draw(menu->menuList[mMovebutton].button, menu->menuList[mMovebutton].dButton);
					TextureManager::Draw(menu->menuList[mMovebutton].tex, menu->menuList[mMovebutton].dTex);

					menu->boardStatus = -1;
					TextureManager::Draw(menu->caroGame, menu->dBoard);

				}

				TextureManager::Draw(menu->menuList[menuList_itr].isActivated, menu->menuList[menuList_itr].dButton);
				TextureManager::Draw(menu->menuList[menuList_itr].tex, menu->menuList[menuList_itr].dTex);
			}

			mMovebutton = menuList_itr;

			return;
		}
	}

	if (mMovebutton != 0 && (mMovebutton != modeNum + 1 || modeNum == 0))
	{
		TextureManager::Draw(menu->menuList[mMovebutton].button, menu->menuList[mMovebutton].dButton);
		TextureManager::Draw(menu->menuList[mMovebutton].tex, menu->menuList[mMovebutton].dTex);
		mMovebutton = 0;
		menu->boardStatus = -1;
		TextureManager::Draw(menu->caroGame, menu->dBoard);
	}

}

void Game::mouseButtonDown_inMenu()
{
	for (int menuList_itr = 1; menuList_itr <= 7; ++menuList_itr)
	{
		if (xMouse > menu->menuList[menuList_itr].x && xMouse < menu->menuList[menuList_itr].x + menu->menuList[menuList_itr].w
			&& yMouse > menu->menuList[menuList_itr].y && yMouse < menu->menuList[menuList_itr].y + menu->menuList[menuList_itr].h)
		{
			mDownbutton = menuList_itr;
			return;
		}
	}
}

void Game::mouseButtonUp_inMenu()
{
	for (int menuList_itr = 1; menuList_itr <= 7; ++menuList_itr)
	{
		if (xMouse > menu->menuList[menuList_itr].x && xMouse < menu->menuList[menuList_itr].x + menu->menuList[menuList_itr].w
			&& yMouse > menu->menuList[menuList_itr].y && yMouse < menu->menuList[menuList_itr].y + menu->menuList[menuList_itr].h)
		{
			if (mDownbutton == menuList_itr)
			{
				switch (menuList_itr)
				{
				case 1:
				{
					menu->boardStatus = (menu->boardStatus + 1) % 2;
					if (menu->boardStatus == 0)
					{
						TextureManager::Draw(menu->manualBoard, menu->dBoard);
					}
					else
					{
						TextureManager::Draw(menu->infoBoard, menu->dBoard);
					}
					break;
				}
				case 2:
				{
					if (modeNum == 1)
					{
						modeNum = 0;
						newGame = false;
						TextureManager::Draw(menu->menuList[2].button, menu->menuList[2].dButton);
						TextureManager::Draw(menu->menuList[2].tex, menu->menuList[2].dTex);
					}
					else
					{
						if (modeNum == 2)
						{
							TextureManager::Draw(menu->menuList[3].button, menu->menuList[3].dButton);
							TextureManager::Draw(menu->menuList[3].tex, menu->menuList[3].dTex);
						}
						modeNum = 1;
						TextureManager::Draw(menu->menuList[2].isActivated, menu->menuList[2].dButton);
						TextureManager::Draw(menu->menuList[2].tex, menu->menuList[2].dTex);
					}
					newGame = false;
					restart();
					break;
				}
				case 3:
				{
					if (modeNum == 2)
					{
						modeNum = 0;
						newGame = false;
						TextureManager::Draw(menu->menuList[3].button, menu->menuList[3].dButton);
						TextureManager::Draw(menu->menuList[3].tex, menu->menuList[3].dTex);
					}
					else
					{
						if (modeNum == 1)
						{
							TextureManager::Draw(menu->menuList[2].button, menu->menuList[2].dButton);
							TextureManager::Draw(menu->menuList[2].tex, menu->menuList[2].dTex);
						}
						modeNum = 2;
						TextureManager::Draw(menu->menuList[3].isActivated, menu->menuList[3].dButton);
						TextureManager::Draw(menu->menuList[3].tex, menu->menuList[3].dTex);
					}
					newGame = false;
					restart();
					break;
				}
				case 4:
				{
					restart();
					break;
				}
				case 5:
				{
					for (int undo_itr = 1; undo_itr <= modeNum; ++undo_itr)
					{
						map->undo();
						map->renderEvent(2, xMsave, yMsave);
						map->renderEvent(3, xKey, yKey);
					}
					break;
				}
				case 6:
				{
					for (int redo_itr = 1; redo_itr <= modeNum; ++redo_itr) map->redo();
					break;
				}
				case 7:
				{
					isRunning = menu->Quitevent();
					if (isRunning) restart();
				}
				}
			}

			return;
		}
	}

}


void Game::twoPlayerMode()
{
	while (isRunning && modeNum == 1)
	{
		handleEvents();
		if (map->check() != -1)
		{
			cout << "endgame with player " << map->check() + 1 << " win" << endl;
			menu->endGame(map->check() + 1);
			restart();
		}
		else if (map->isContinue == false)
		{
			cout << "Game is tie !" << endl;
			menu->endGame(5);
			restart();
		}
	}
}


void Game::onePlayerMode()
{
	comFlag = rand() % 2 +1;
	if (comFlag == 1) conputerTurn = true;

	while (isRunning && modeNum == 2)
	{
		handleEvents();
		if (map->check() != -1)
		{
			cout << "endgame with player " << map->check() + 1 << " win" << endl;
			menu->endGame(3);
			restart();
			comFlag = 2;
		}
		else if (map->isContinue == false)
		{
			cout << "Game is tie !" << endl;
			menu->endGame(5);
			restart();
		}

		if (conputerTurn)
		{
			map->AI(comFlag);
			conputerTurn = false;

			if (map->check() != -1)
			{
				cout << "endgame with player " << map->check() + 1 << " win" << endl;
				menu->endGame(4);
				restart();
				comFlag = 1;
				conputerTurn = true;
				SDL_Delay(500);
			}
			else if (map->isContinue == false)
			{
				cout << "Game is tie !" << endl;
				menu->endGame(5);
				restart();
			}
		}
	}
}



void Game::restart()
{

	turn = -1;
	map->LoadMap();
	map->DrawMap();
	xMsave = 11;
	yMsave = 10;
	xKey = yKey = 10;
	map->winner = -1;
	conputerTurn = false;

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


