#pragma once
#include"Game.h"
//incarc si desenez texturile incarcate
class ManagerTexturi {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
	static void DrawTex(SDL_Texture* tex, SDL_Rect dest);
};