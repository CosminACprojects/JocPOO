#include"ManagerTexturi.h"

SDL_Texture* ManagerTexturi::LoadTexture(const char* fileName) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}
void ManagerTexturi::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}
void ManagerTexturi::DrawTex(SDL_Texture* tex, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, tex, NULL, &dest);
}