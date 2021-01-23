#include "TextureManager.h"


SDL_Texture* TextureManager::loadTexture(const char* texture)
{
	SDL_Surface* pSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, pSurface);

	SDL_FreeSurface(pSurface);

	return tex;
}

SDL_Texture* TextureManager::loadFont(TTF_Font *font, const string &content, int size, const SDL_Color &color)
{
	SDL_Surface* pSurface = TTF_RenderText_Solid(font, content.c_str(), color);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, pSurface);
	SDL_FreeSurface(pSurface);

	return tex;
}

void TextureManager::Draw(SDL_Texture *image, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, image, NULL, &dest);
	SDL_RenderPresent(Game::renderer);
}