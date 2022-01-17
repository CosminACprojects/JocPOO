#pragma once
#include"SistemEntitate-Component.h"
#include"ManagerDeComponente.h"
#include"Vector2D.h"

//retine si updateaza pozitia proiectilului 
class ComponentProiectil :public Component {
	ComponentPozitie* pozitie;
	int range = 0;
	int speed = 0;
	int distance = 0;
	Vector2D viteza;
public:
	ComponentProiectil(int rng, int sp, Vector2D vel) :range(rng), speed(sp), viteza(vel) {}
	~ComponentProiectil() {};
	void init()override
	{
		pozitie = &entity->getComponent<ComponentPozitie>();
		pozitie->viteza = viteza;
	}
	void update()override
	{
		distance += speed;
		if (distance > range)
		{
			entity->destroy();
		}
	}
};
