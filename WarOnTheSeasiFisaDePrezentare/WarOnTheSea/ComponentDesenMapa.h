#pragma once
#include"SistemEntitate-Component.h"
#include"SDL.h"
#include"ManagerCreareProiectileSiTexturi.h"
//mapa de joc este desenata patratica cu patratica folosind un srcRect.x reprezentand pozitia tile-ului 
//respectiv din harta.png-(ID-ul trimis) (01 reprezentand de ex -randul 0 coloana 1 unde se afla imaginea apei) 
class ComponentDesenMapa :public Component {
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	ComponentDesenMapa() = default;
	~ComponentDesenMapa() {
		SDL_DestroyTexture(texture);
	}
	ComponentDesenMapa(int srcX, int srcY, int xpos, int ypos, std::string id) {
		texture = Game::assets->GetTexture(id);

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = 32;

		destRect.x = xpos;
		destRect.y = ypos;
		destRect.w = destRect.h = 32;
	}

	void draw()override {
		ManagerTexturi::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};