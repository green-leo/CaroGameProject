#pragma once
#include "Game.h"
#include <vector>

class Map
{
public:
	Map();
	~Map();

	void LoadMap();
	void DrawMap();
	void Update(int turn, int col, int row);
	void renderEvent(int type, int col, int row);
	void undo();
	void redo();
	void remakeList();

	void AI(int comFlag);
	void evalBoard(int playerflag);
	void alphaBeta(int alpha, int beta, int depth, int playerflag);
	int maxValue(int alpha, int beta, int depth);
	int minValue(int alpha, int beta, int depth);
	pair<int, int> buil_listMax();
	int max_boardScore();
	int compareMax(int a, int b);
	int compareMin(int a, int b);
	int checkEnd(int row, int col);

	int check();
	bool horizontal();
	bool vertical();
	bool cross();
	
	int map[25][25];
	static bool isContinue;
	static int winner; //0 for X, 1 for O, -1 for tie (hòa)
	bool re_undo = false;
	
private:

	SDL_Texture* table; //render in DrawMap for good speed, made by 20*20 square
	SDL_Texture* square; //-1;
	SDL_Texture* X; //0
	SDL_Texture* O; //1
	SDL_Texture* mouseMove; //2
	SDL_Texture* keyMove; //3
	SDL_Texture* outMove; //4
	SDL_Rect dest;
	SDL_Rect dTable;

	int turnTotal = 0;

	typedef struct Point
	{
		int type;
		int row, col;
	} Point;

	vector <Point> pList;

	int boardScore[25][25];

	int maxDepth = 6;
	int maxMove = 4;

	int AScore[6] = { 0,4,28,256,2308 };// Mang diem tan cong 0,4,28,256,2308
	int DScore[6] = { 0,1,9,85,769 };  // Mang diem phong ngu 0,1,9,85,769

	pair<int, int> nextPoint;



};
