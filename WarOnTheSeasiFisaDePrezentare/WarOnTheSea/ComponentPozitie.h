#pragma once
#include"ManagerDeComponente.h"
#include"Vector2D.h"
#include"SDL_mixer.h"

//retin pozitia si viteza entitatilor care au acest 

class ComponentPozitie :public Component
{
public:

	Vector2D pozitie;
	Vector2D viteza;
	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 4;



	ComponentPozitie() {
		pozitie.Zero();

	}
	ComponentPozitie(float x, float y, int sc) {
		pozitie.x = x;
		pozitie.y = y;
		scale = sc;
	}
	ComponentPozitie(int sc)
	{
		scale = sc;
	}
	ComponentPozitie(float x, float y, int h, int w, int sc) {
		pozitie.x = x;
		pozitie.y = y;
		height = h;
		width = w;
		scale = sc;
	}


	void init()override {
		viteza.Zero();
	}
	void update()override {
		pozitie.x += viteza.x * speed;
		pozitie.y += viteza.y * speed;
	}
};
