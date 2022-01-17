#pragma once
#include<map>
#include<string>
#include"ManagerTexturi.h"
#include"Vector2D.h"
#include"SistemEntitate-Component.H"
//pozitie path-ul imaginii din care iau tile-urile intr-un string id si totodata fac proiectilele
class ManagerCreareProiectileSiTexturi {
	Manager* manager;
	std::map<std::string, SDL_Texture*>textures;
public:
	ManagerCreareProiectileSiTexturi(Manager* man);
	~ManagerCreareProiectileSiTexturi();
	//functiile ce creaza proiectilele celor 2 playeri in functie de pozitia lor 
	void CreateProjectileplayer1(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
	void CreateProjectileplayer2(Vector2D pos, Vector2D vel, int range, int speed, std::string id);
	//management de texturi
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);
};

