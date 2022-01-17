#pragma once
#include"ManagerDeComponente.h"
#include"SDL.h"
#include"ManagerTexturi.h"
#include"ManagerCreareProiectileSiTexturi.h"
#include"Barca.h"
#include<map>
//se ocupa de repozitionarea playerilor si a proiectilelor 

class ComponentImagine :public Component
{
	ComponentPozitie* pozitie;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool IsBarca = false;


public:
	int barcaIndex = 0;

	std::map<std::string, Barca> barci;

	SDL_RendererFlip imaginesipozitieFlip = SDL_FLIP_NONE;

	ComponentImagine() = default;
	ComponentImagine(std::string id) {
		setTex(id);
	}
	ComponentImagine(std::string id, bool isbarca)
	{
		setTex(id);
		IsBarca = isbarca;

		Barca orizontal = Barca(0);
		Barca vertical = Barca(1);

		barci.emplace("Orizontal", orizontal);
		barci.emplace("Vertical", vertical);

		Pozitie("Orizontal");
	}

	~ComponentImagine() {
	}
	void setTex(std::string id) {
		texture = Game::assets->GetTexture(id);
	}

	void init()override {

		pozitie = &entity->getComponent<ComponentPozitie>();
		srcRect.x = srcRect.y = 0;
		srcRect.w = pozitie->width;
		srcRect.h = pozitie->height;

	}
	void update()override {

		srcRect.y = barcaIndex * pozitie->height;
		destRect.x = static_cast<int>(pozitie->pozitie.x);
		destRect.y = static_cast<int>(pozitie->pozitie.y);
		destRect.w = pozitie->width * pozitie->scale;
		destRect.h = pozitie->height * pozitie->scale;
	}
	void draw() {
		ManagerTexturi::Draw(texture, srcRect, destRect, imaginesipozitieFlip);
	}
	void Pozitie(std::string felBarca)
	{
		barcaIndex = barci[felBarca].index;
	}
	bool daca() {
		return IsBarca;
	}
};

