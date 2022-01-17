#pragma once
#include"Game.h"
#include"SistemEntitate-Component.h"
#include"ManagerDeComponente.h"
//controale pentru player2
static int Z;
static int W;

class KeyboardControllerplayer2 :public Component {
public:
	ComponentPozitie* pozitie;
	Mix_Chunk* shotEffect = Mix_LoadWAV("gun_fire.wav");
	ComponentImagine* imaginesipozitie;
	int viteza1 = 1;
	void init() override
	{
		pozitie = &entity->getComponent<ComponentPozitie>();
		imaginesipozitie = &entity->getComponent<ComponentImagine>();
	}

	void update()override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				pozitie->viteza.y = -1;
				imaginesipozitie->Pozitie("Vertical");
				if (imaginesipozitie->daca())
				{
					imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				}
				Z = pozitie->viteza.x;
				W = pozitie->viteza.y;
				break;
			case SDLK_LEFT:
				pozitie->viteza.x = -1;
				Z = pozitie->viteza.x;
				W = pozitie->viteza.y;
				imaginesipozitie->Pozitie("Orizontal");
				imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				break;
			case SDLK_RIGHT:
				pozitie->viteza.x = 1;
				Z = pozitie->viteza.x;
				W = pozitie->viteza.y;
				imaginesipozitie->Pozitie("Orizontal");
				imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_DOWN:
				pozitie->viteza.y = 1;
				Z = pozitie->viteza.x;
				W = pozitie->viteza.y;
				imaginesipozitie->Pozitie("Vertical");
				if (imaginesipozitie->daca())
				{
					imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_VERTICAL;
				}
				break;
			case SDLK_KP_PLUS:
				bool ok = 0;
				if (pozitie->viteza.x == 0 && pozitie->viteza.y == 0)
				{
					pozitie->viteza.x = 1;
					ok = 1;
				};
				static int x = 0;
				if (x % 2 == 0)
				{

					if (Z != 0 && W == 0)
					{
						Game::assets->CreateProjectileplayer2(Vector2D(pozitie->pozitie.x, pozitie->pozitie.y + 32), Vector2D(Z * 2 * viteza1, W * viteza1), 400, 2, "bombaplayer1");
					}
					if (W != 0 && Z == 0)
					{
						Game::assets->CreateProjectileplayer2(Vector2D(pozitie->pozitie.x, pozitie->pozitie.y + 32), Vector2D(Z * viteza1, W * 2 * viteza1), 400, 2, "bombaplayer1");

					}
					if (Z != 0 && W != 0)
					{
						Game::assets->CreateProjectileplayer2(Vector2D(pozitie->pozitie.x, pozitie->pozitie.y + 32), Vector2D(Z * viteza1, W * 2 * viteza1), 400, 2, "bombaplayer1");
					}
					x = 0;
				};
				x++;
				if (ok)
					pozitie->viteza.x = 0;
				Mix_PlayChannel(-1, shotEffect, 0);
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_UP:
				pozitie->viteza.y = 0;
				imaginesipozitie->Pozitie("Vertical");
				//imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_VERTICAL;
				break;
			case SDLK_LEFT:
				pozitie->viteza.x = 0;
				imaginesipozitie->Pozitie("Orizontal");
				//imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				break;
			case SDLK_RIGHT:
				pozitie->viteza.x = 0;
				imaginesipozitie->Pozitie("Orizontal");
				break;
			case SDLK_DOWN:
				pozitie->viteza.y = 0;
				imaginesipozitie->Pozitie("Orizontal");
				imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				break;
			case SDLK_KP_PLUS:
				if (Z == W)
				{
					Z = 0;
				}
				break;
			}
		}
	}
};
