#pragma once
#define SDL_MAIN_HANDLED
#include"SDL.h"
#include<iostream>
#include"SDL_image.h"
#include<vector>
#include"SDL_mixer.h"
class ManagerCreareProiectileSiTexturi;
class ComponentColiziune;

class Game {
	SDL_Window* window;
	SDL_Texture* loading, * winp1, * winp2;

public:
	Mix_Music* backgroundSound;
	SDL_Rect dest;
	static bool IsRunning;
	static bool startjoc;
	static bool p1win;
	static bool p2win;
	static bool replay;
	static bool reinit;
	static bool music;
	static bool on;

	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);


	void handleEvents();
	void update();
	void draw();
	void clean();
	bool running() { return (IsRunning); }
	void incarcareloadingscreen();
	void checkloadingplay();
	void incarcarewin1();
	void incarcarewin2();
	void checkgotoloading();
	void ReInit();
	void falsereinit() { reinit = false; };
	void PlayOrStopMusic();

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static ManagerCreareProiectileSiTexturi* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupplayers,
		groupColliders,
		groupproiectileleplayer1,
		groupproiectileleplayer2,
		groupBonusuri,
		groupBonusViteza
	};
};



