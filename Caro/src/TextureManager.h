#pragma once
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture *loadTexture(const char* texture);
	static SDL_Texture *loadFont(TTF_Font *font, const string &content, int size, const SDL_Color &color);
	static void Draw(SDL_Texture *image, SDL_Rect dest);
};