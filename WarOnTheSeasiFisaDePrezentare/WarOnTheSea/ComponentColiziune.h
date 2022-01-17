#pragma once
#include<string>
#include"SDL.h"
#include"ManagerDeComponente.h"
#include"ManagerTexturi.h"
//verifica coliziunile de pe mapa
class ComponentColiziune :public Component
{
public:
	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcR, destR;

	ComponentPozitie* pozitie;

	ComponentColiziune(std::string t)
	{
		tag = t;
	}
	ComponentColiziune(std::string t, int xpos, int ypos, int size)
	{
		tag = t;
		collider.x = xpos;
		collider.y = ypos;
		collider.h = collider.w = size;
	}
	void init() override
	{
		if (!entity->hasComponent<ComponentPozitie>())
		{
			entity->addComponent<ComponentPozitie>();
		}
		pozitie = &entity->getComponent<ComponentPozitie>();

		tex = ManagerTexturi::LoadTexture("assets/coltext.png");
		srcR = { 0,0,32,32 };
		destR = { collider.x,collider.y,collider.w,collider.h };

	}

	void update()override {
		if (tag != "harta")
		{
			collider.x = static_cast<int>(pozitie->pozitie.x);
			collider.y = static_cast<int>(pozitie->pozitie.y);
			collider.w = static_cast<int>(pozitie->width * pozitie->scale);
			collider.h = static_cast<int>(pozitie->height * pozitie->scale);
		}
	}
	void draw()override {
		ManagerTexturi::Draw(tex, srcR, destR, SDL_FLIP_NONE);
	}
};
