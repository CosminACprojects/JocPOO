#pragma once
#include"Game.h"
#include"SistemEntitate-Component.h"
#include"ManagerDeComponente.h"
#include"SDL_mixer.h"
//controalele de pe tastatura pentru player 1
static int X;
static int Y;
class KeyboardController :public Component {
public:
	Mix_Music* backgroundSoundS = Mix_LoadMUS("melodiefundal.mp3");
	Mix_Chunk* shotEffect = Mix_LoadWAV("gun_fire.wav");
	ComponentPozitie* pozitie;
	ComponentImagine* imaginesipozitie;
	int viteza2 = 1;

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
			case SDLK_w:
				pozitie->viteza.y = -1;
				Y = pozitie->viteza.y;
				X = pozitie->viteza.x;
				imaginesipozitie->Pozitie("Vertical");
				if (imaginesipozitie->daca())
				{
					imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				}

				break;
			case SDLK_a:
				pozitie->viteza.x = -1;
				X = pozitie->viteza.x;
				Y = pozitie->viteza.y;
				imaginesipozitie->Pozitie("Orizontal");
				imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_d:
				pozitie->viteza.x = 1;
				X = pozitie->viteza.x;
				Y = pozitie->viteza.y;
				imaginesipozitie->Pozitie("Orizontal");
				imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				break;
			case SDLK_s:
				pozitie->viteza.y = 1;
				Y = pozitie->viteza.y;
				X = pozitie->viteza.x;
				imaginesipozitie->Pozitie("Vertical");
				if (imaginesipozitie->daca())
				{
					imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_VERTICAL;
				}
				break;
			case SDLK_g:
				bool ok = 0;
				if (X == 0 && Y == 0)
				{
					X = 1;
					ok = 1;
				};
				static int x = 0;
				if (x % 2 == 0)
				{

					if (X != 0 && Y == 0)
					{
						Game::assets->CreateProjectileplayer1(Vector2D(pozitie->pozitie.x, pozitie->pozitie.y + 32), Vector2D(X * 2 * viteza2, Y * viteza2), 400, 2, "bombaplayer1");
					}
					if (Y != 0 && X == 0)
					{
						Game::assets->CreateProjectileplayer1(Vector2D(pozitie->pozitie.x, pozitie->pozitie.y + 32), Vector2D(X * viteza2, Y * 2 * viteza2), 400, 2, "bombaplayer1");

					}
					if (X != 0 && Y != 0)
					{
						Game::assets->CreateProjectileplayer1(Vector2D(pozitie->pozitie.x, pozitie->pozitie.y + 32), Vector2D(X * viteza2, Y * 2 * viteza2), 400, 2, "bombaplayer1");
					}
					x = 0;
				}
				x++;
				if (ok)
					X = 0;
				Mix_PlayChannel(-1, shotEffect, 0);
				break;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				pozitie->viteza.y = 0;
				imaginesipozitie->Pozitie("Vertical");
				//imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_VERTICAL;
				break;
			case SDLK_a:
				pozitie->viteza.x = 0;
				imaginesipozitie->Pozitie("Orizontal");
				//imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				break;
			case SDLK_d:
				pozitie->viteza.x = 0;
				imaginesipozitie->Pozitie("Orizontal");
				break;
			case SDLK_s:
				pozitie->viteza.y = 0;
				imaginesipozitie->Pozitie("Orizontal");
				imaginesipozitie->imaginesipozitieFlip = SDL_FLIP_NONE;
				break;
			case SDLK_m:
				if (Game::on)
				{
					Mix_PlayMusic(backgroundSoundS, -1);
					Game::on = false;
				}
				else {
					Mix_PauseMusic();
					Game::on = true;
				}
				break;
			case SDLK_g:
				if (X == Y)
				{
					pozitie->viteza.y = 0;
				}
				break;


			case SDLK_ESCAPE:
				Game::IsRunning = false;
				break;
			}
		}
	}
};
