#include "Map.h"
#include "TextureManager.h"

#include <cstdlib>


bool Map::isContinue = true;
int Map::winner = -1;

Map::Map()
{
	square = TextureManager::loadTexture("image/square.png");
	X = TextureManager::loadTexture("image/X.png");
	O = TextureManager::loadTexture("image/O.png");
	mouseMove = TextureManager::loadTexture("image/mouseMove.png");
	keyMove = TextureManager::loadTexture("image/keyMove.png");
	outMove = TextureManager::loadTexture("image/outMove.png");
	
	dest.w = dest.h = 30;
	dTable.x = dTable.y = 5;
	dTable.w = dTable.h = 600;
}
Map::~Map()
{}

void Map::LoadMap()
{
	for (int row = 0; row <= 21; row++)
		for (int col = 0; col <= 21; col++)
			map[row][col] = -1;

	for (int row = 1; row <= 20; ++row)
		for (int col = 1; col <= 20; ++col)
		{
			dest.x = (col - 1) * 30 + 5;
			dest.y = (row - 1) * 30 + 5;
			SDL_RenderCopy(Game::renderer, square, NULL, &dest);
		}

	SDL_SetRenderTarget(Game::renderer, table);
	pList.clear();
	turnTotal = 0;
}

void Map::DrawMap()
{
	TextureManager::Draw(table, dTable);
	renderEvent(2, 11, 10);
	renderEvent(3, 10, 10);
}

void Map::Update(int turn, int col, int row)
{
	if (re_undo)
	{
		remakeList();
		re_undo = false;
	}

	map[row][col] = turn;
	++turnTotal;

	Point newPoint;
	newPoint.type = turn;
	newPoint.row = row;
	newPoint.col = col;
	pList.push_back(newPoint);

	switch (turn)
	{
	case 0:
	{
		dest.x = (col - 1) * 30 + 5;
		dest.y = (row - 1) * 30 + 5;
		TextureManager::Draw(X, dest);
		break;
	}
	case 1:
	{
		dest.x = (col - 1) * 30 + 5;
		dest.y = (row - 1) * 30 + 5;
		TextureManager::Draw(O, dest);
		break;
	}
	}

}

void Map::renderEvent(int type, int col, int row)
{
	switch (type)
	{
	case 4:
	{
		dest.x = (col - 1) * 30 + 5;
		dest.y = (row - 1) * 30 + 5;
		TextureManager::Draw(outMove, dest);
		break;
	}
	case 3:
	{
		dest.x = (col - 1) * 30 + 5;
		dest.y = (row - 1) * 30 + 5;
		TextureManager::Draw(keyMove, dest);
		break;
	}
	case 2:
	{
		dest.x = (col - 1) * 30 + 5;
		dest.y = (row - 1) * 30 + 5;
		TextureManager::Draw(mouseMove, dest);
		break;
	}
	case -1:
	{
		map[row][col] = -1;
		dest.x = (col - 1) * 30 + 5;
		dest.y = (row - 1) * 30 + 5;
		TextureManager::Draw(square, dest);
		break;
	}
	}
}

void Map::undo()
{
	if (turnTotal > 0)
	{
		Point p;
		p = pList[--turnTotal];
		renderEvent(-1, p.col, p.row);

		map[p.row][p.col] = -1;
		Game::turn = (Game::turn + 1) % 2;

		re_undo = true;
	}

}

void Map::redo()
{

	if (turnTotal < pList.size())
	{
		Point p;
		p = pList[turnTotal];

		map[p.row][p.col] = p.type;
		++turnTotal;
		Game::turn = (Game::turn + 1) % 2;

		switch (p.type)
		{
		case 0:
		{
			dest.x = (p.col - 1) * 30 + 5;
			dest.y = (p.row - 1) * 30 + 5;
			TextureManager::Draw(X, dest);
			break;
		}
		case 1:
		{
			dest.x = (p.col - 1) * 30 + 5;
			dest.y = (p.row - 1) * 30 + 5;
			TextureManager::Draw(O, dest);
			break;
		}
		}


		re_undo = true;
	}

}

void Map::remakeList()
{
	while (pList.size() != turnTotal) pList.pop_back();

}

int Map::check()
{
	if (turnTotal == 400) isContinue = false;
	else isContinue = true;

	horizontal();
	vertical();
	cross();

	return winner;
}

bool Map::horizontal()
{
	for (int row = 1; row <= 20; ++row)
		for (int col = 1; col <= 16; ++col)
			if (map[row][col] != -1)
				if (map[row][col] == map[row][col + 1] && map[row][col] == map[row][col + 2] && map[row][col] == map[row][col + 3] && map[row][col] == map[row][col + 4] && (map[row][col - 1] == -1 || map[row][col + 5] == -1))
				{
					winner = map[row][col];
					return true;
				}
	return false;
}
bool Map::vertical()
{
	for (int row = 1; row <= 16; ++row)
		for (int col = 1; col <= 20; ++col)
			if (map[row][col] != -1)
				if (map[row][col] == map[row + 1][col] && map[row][col] == map[row + 2][col] && map[row][col] == map[row + 3][col] && map[row][col] == map[row + 4][col] && (map[row - 1][col] == -1 || map[row + 5][col] == -1))
				{
					winner = map[row][col];
					return true;
				}
	return false;
}

bool Map::cross()
{
	for (int row = 1; row <= 16; ++row)
		for (int col = 1; col <= 16; ++col)
			if (map[row][col] != -1)
				if (map[row][col] == map[row + 1][col + 1] && map[row][col] == map[row + 2][col + 2] && map[row][col] == map[row + 3][col + 3] && map[row][col] == map[row + 4][col + 4] && (map[row - 1][col - 1] == -1 || map[row + 5][col + 5] == -1))
				{
					winner = map[row][col];
					return true;
				}
	for (int row = 1; row <= 16; ++row)
		for (int col = 5; col <= 20; ++col)
			if (map[row][col] != -1)
				if (map[row][col] == map[row + 1][col - 1] && map[row][col] == map[row + 2][col - 2] && map[row][col] == map[row + 3][col - 3] && map[row][col] == map[row + 4][col - 4] && (map[row - 1][col + 1] == -1 || map[row + 5][col - 5] == -1))
				{
					winner = map[row][col];
					return true;
				}

	return false;
}

void Map::AI(int comFlag)
{
	/*	evalBoard(comFlag);
	nextPoint = buil_listMax();

	Game::turn = (Game::turn + 1) % 2;
	Update(Game::turn, nextPoint.second, nextPoint.first);
		*/
	
	if (turnTotal == 0)
	{
		Game::turn = (Game::turn + 1) % 2;
		Update(Game::turn, 10, 10);

		return;
	}

	alphaBeta(0, 1, 2, comFlag);
	Game::turn = (Game::turn + 1) % 2;
	Update(Game::turn, nextPoint.second, nextPoint.first);

	renderEvent(4, Game::xKey, Game::yKey);
	Game::xKey = nextPoint.second;
	Game::yKey = nextPoint.first;
	renderEvent(3, Game::xKey, Game::yKey);

	return;
	
}

void Map::evalBoard(int playerflag)
{

	for (int i = 0; i <= 24; ++i)
		for (int j = 0; j <= 24; ++j)
			boardScore[i][j] = 0;


	int row, col;
	int eP1, eP2;

	//browse horizontal
	for (row = 1; row <= 20; ++row)
		for (col = 1; col <= 20 - 4; ++col)
		{
			eP1 = eP2 = 0;
			for (int add = 0; add <= 4; ++add)
			{
				if (map[row][col + add] == 0) ++eP1;
				if (map[row][col + add] == 1) ++eP2;
			}
			//trong cong 5 o chi co 1 eplayer ?
			if (eP1*eP2 == 0 && eP1 != eP2)
				for (int add = 0; add <= 4; ++add)
				{
					if (map[row][col + add] == -1)
					{
						if (eP1 == 0)
							if (map[row][col - 1] != 0 || map[row][col + 5] != 0)
								if (playerflag == 1) boardScore[row][col + add] += DScore[eP2];
								else boardScore[row][col + add] += AScore[eP2];
						if (eP2 == 0)
							if (map[row][col - 1] != 1 || map[row][col + 5] != 1)
								if (playerflag == 2) boardScore[row][col + add] += DScore[eP1];
								else boardScore[row][col + add] += AScore[eP1];
						if (eP1 == 4 || eP2 == 4) boardScore[row][col + 1] *= 2;
					}
				}
		}

	//browse vertical		
	for (col = 1; col <= 20; ++col)
		for (row = 1; row <= 20 - 4; ++row)
		{
			eP1 = eP2 = 0;
			for (int add = 0; add <= 4; ++add)
			{
				if (map[row + add][col] == 0) ++eP1;
				if (map[row + add][col] == 1) ++eP2;
			}
			//trong vong 5 o chi co 1 player
			if (eP1*eP2 == 0 && eP1 != eP2)
				for (int add = 0; add <= 4; ++add)
				{
					if (map[row + add][col] == -1)
					{
						if (eP1 == 0)
							if (map[row - 1][col] != 0 || map[row + 5][col] != 0)
								if (playerflag == 1) boardScore[row + add][col] += DScore[eP2];
								else boardScore[row + add][col] += AScore[eP2];
						if (eP2 == 0)
							if (map[row][col - 1] != 1 || map[row][col + 5] != 1)
								if (playerflag == 2) boardScore[row + add][col] += DScore[eP1];
								else boardScore[row + add][col] += AScore[eP1];
						if (eP1 == 4 || eP2 == 4)
							boardScore[row + add][col] *= 2;
					}

				}
		}

	//browse diagonal down
	for (row = 1; row <= 20 - 4; ++row)
		for (col = 1; col <= 20 - 4; ++col)
		{
			eP1 = eP2 = 0;
			for (int add = 0; add <= 4; ++add)
			{
				if (map[row + add][col + add] == 0) ++eP1;
				if (map[row + add][col + add] == 1) ++eP2;
			}
			if (eP1 * eP2 == 0 && eP1 != eP2)
				for (int add = 0; add <= 4; ++add)
				{
					if (map[row + add][col + add] == -1)
					{
						if (eP1 == 0)
							if (map[row - 1][col - 1] != 0 || map[row + 5][col + 5] != 0)
								if (playerflag == 1) boardScore[row + add][col + add] += DScore[eP2];
								else boardScore[row + add][col + add] += AScore[eP2];
						if (eP2 == 0)
							if (map[row - 1][col - 1] != 1 || map[row + 5][col + 5] != 1)
								if (playerflag == 2) boardScore[row + add][col + add] += DScore[eP1];
								else boardScore[row + add][col + add] += AScore[eP1];
						if (eP1 == 4 || eP2 == 4)
							boardScore[row + add][col + add] *= 2;
					}
				}
		}

	//browse diagonal up
	for (row = 4; row <= 20; ++row)
		for (col = 1; col <= 20 - 4; ++col)
		{
			eP1 = eP2 = 0;
			for (int add = 0; add <= 4; ++add)
			{
				if (map[row - add][col + add] == 0) ++eP1;
				if (map[row - add][col + add] == 1) ++eP2;
			}
			if (eP1 * eP2 == 0 && eP1 != eP2)
				for (int add = 0; add <= 4; ++add)
				{
					if (map[row - add][col + add] == -1)
					{
						if (eP1 == 0)
							if (map[row + 1][col - 1] != 0 || map[row - 5][col + 5] != 0)
								if (playerflag == 1) boardScore[row - add][col + add] += DScore[eP2];
								else boardScore[row - add][col + add] += AScore[eP2];
						if (eP2 == 0)
							if (map[row + 1][col - 1] != 1 || map[row - 5][col + 5] != 1)
								if (playerflag == 2) boardScore[row - add][col + add] += DScore[eP1];
								else boardScore[row - add][col + add] += AScore[eP1];
						if (eP1 == 4 || eP2 == 4)
							boardScore[row - add][col + add] *= 2;
					}
				}
		}



}

//alpha-beta algorithm
void Map::alphaBeta(int alpha, int beta, int depth, int playerflag)
{
	if (playerflag == 2)
	{
		maxValue(alpha, beta, depth);
	}
	else
	{
		minValue(alpha, beta, depth);
	}
}


int Map::maxValue(int alpha, int beta, int depth)
{
	evalBoard(2);
	if (depth >= maxDepth)
	{
		return max_boardScore();
	}

	evalBoard(2);
	vector <pair<int, int>> listMax;
	
	for (int i = 0; i < maxMove; ++i)
	{
		pair<int, int> p = buil_listMax();
		if (p.first == 0) break;
		listMax.push_back(p);

		boardScore[p.first][p.second] = 0;
	}

	int v = -21474836;
	for (int i = 0; i < listMax.size(); ++i)
	{
		pair<int, int> com = listMax[i];

		map[com.first][com.second] = 1;
		v = compareMax(v, minValue(alpha, beta, depth + 1));
		map[com.first][com.second] = -1;

		if (v >= beta ) //|| checkEnd(com.first, com.second) == 1 )
		{
			nextPoint = com;
			return v;
		}
		
		alpha = compareMax(alpha, v);
	}

	return v;

}

int Map::minValue(int alpha, int beta, int depth)
{
	evalBoard(1);
	if (depth >= maxDepth)
	{
		return max_boardScore();
	}
	
	evalBoard(1);
	vector <pair<int, int>> listMax;

	for (int i = 0; i < maxMove; ++i)
	{
		pair<int, int> p = buil_listMax();
		if (p.first == 0) break;
		listMax.push_back(p);

		boardScore[p.first][p.second] = 0;
	}

	int v = 21474836;
	for (int i = 0; i < listMax.size(); ++i)
	{
		pair<int, int> com = listMax[i];

		map[com.first][com.second] = 0;
		v = compareMin(v, maxValue(alpha, beta, depth + 1));
		map[com.first][com.second] = -1;

		if (v <= alpha ) //|| checkEnd(com.first, com.second) == 0)
		{
			return v;
		}
		
		beta = compareMin(beta, v);
	}
	return v;
}


pair<int, int> Map::buil_listMax()
{
	int max = 0;
	pair<int, int> p;

	for (int row = 1; row <= 20; ++row)
		for (int col = 1; col <= 20; ++col)
			if (boardScore[row][col] > max)
			{
				max = boardScore[row][col];

				p.first = row;
				p.second = col;
			}

	if (max = 0)
	{
		p.first = 0;
		p.second = 0;
	}

	return p;
}

int Map::max_boardScore()
{
	int max = 0;

	for (int row = 1; row <= 20; ++row)
		for (int col = 1; col <= 20; ++col)
			if (boardScore[row][col] > max)
				max = boardScore[row][col];

	return max;
}

int Map::compareMax(int a, int b)
{
	return a >= b ? a : b;
}

int Map::compareMin(int a, int b)
{
	return a <= b ? a : b;
}

int Map::checkEnd(int row, int col) {
	int r = 0, c = 0;
	int i;
	bool human, pc;
	// Check hang ngang
	while (c < 20 - 4) {
		human = true;
		pc = true;
		for (i = 0; i < 5; i++) {
			if (map[row][c + i] != 0)
				human = false;
			if (map[row][c + i] != 1)
				pc = false;
		}
		if (human)
			return 0;
		if (pc)
			return 1;
		c++;
	}

	// Check  hang doc
	while (r < 20 - 4) {
		human = true;
		pc = true;
		for (i = 0; i < 5; i++) {
			if (map[r + i][col] != 0)
				human = false;
			if (map[r + i][col] != 1)
				pc = false;
		}
		if (human)
			return 0;
		if (pc)
			return 1;
		r++;
	}

	// Check duong cheo xuong
	r = row;
	c = col;
	while (r > 0 && c > 0) {
		r--;
		c--;
	}
	while (r < 20 - 4 && c < 20 - 4) {
		human = true;
		pc = true;
		for (i = 0; i < 5; i++) {
			if (map[r + i][c + i] != 0)
				human = false;
			if (map[r + i][c + i] != 1)
				pc = false;
		}
		if (human)
			return 0;
		if (pc)
			return 1;
		r++;
		c++;
	}

	// Check duong cheo len
	r = row;
	c = col;
	while (r < 20 - 1 && c > 0) {
		r++;
		c--;
	}

	while (r >= 4 && c < 20 - 4) {
		human = true;
		pc = true;
		for (i = 0; i < 5; i++) {
			if (map[r - i][c + i] != 0)
				human = false;
			if (map[r - i][c + i] != 1)
				pc = false;
		}
		if (human)
			return 0;
		if (pc)
			return 1;
		r--;
		c++;
	}
	return -1;
}
