#include"Game.h"
#include"ManagerTexturi.h"
#include"Map.h"
#include"ManagerDeComponente.h"
#include"Vector2D.h"
#include"TestColiziune.h"
#include<sstream>
#include"ManagerCreareProiectileSiTexturi.h"

bool Game::IsRunning = false;
//cat timp este true jocul ruleaza
bool Game::startjoc = false;
//daca este true jocul intra in mapa de joc 
bool Game::p1win = false;
//castiga player1
bool Game::p2win = false;
//castiga player2
bool Game::replay = false;
bool Game::reinit = false;
//reinitializez datele de inceput in cazul unui replay al jocului
bool Game::music = true;
bool Game::on = true;
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;



ManagerCreareProiectileSiTexturi* Game::assets = new ManagerCreareProiectileSiTexturi(&manager);

auto& player(manager.addEntity());
auto& player2(manager.addEntity());

Game::Game() {}
Game::~Game() {}
//initializarea window texturi pozitii initiale ale playerilor accesul la comenzile de la tastarura si coliziunile playerilor
void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_AUDIO) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		IsRunning = true;
		SDL_ShowCursor(1);
	}
	else {
		IsRunning = false;
	}
	backgroundSound = Mix_LoadMUS("melodiefundal.mp3");
	assets->AddTexture("harta", "assets/harta.png");
	assets->AddTexture("player", "assets/barcuteee.png");
	assets->AddTexture("bombaplayer1", "assets/projectile.png");
	assets->AddTexture("player2", "assets/enemies.png");
	map = new Map("harta", 1, 32);
	map->LoadMap("assets/map.txt", 40, 30);
	loading = ManagerTexturi::LoadTexture("assets/loadingscreen.png");
	winp1 = ManagerTexturi::LoadTexture("assets/winplayer1.png");
	winp2 = ManagerTexturi::LoadTexture("assets/winplayer2.png");



	player.addComponent<ComponentPozitie>(32, 32, 2);
	player.addComponent<ComponentImagine>("player", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ComponentColiziune>("player");
	player.addGroup(groupplayers);

	player2.addComponent<ComponentPozitie>(1184, 864, 2);
	player2.addComponent<ComponentImagine>("player2", true);
	player2.addComponent<KeyboardControllerplayer2>();
	player2.addComponent<ComponentColiziune>("player2");
	player2.addGroup(groupplayers);
}


//folosind auto am posibilitatea de a folosi toate functiile si datele caracteristice componentelor de acelasi tip fara 
//a specifica care-i entitati ii sunt specifice
auto& DesenMapa(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupplayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& proiectileleplayer1(manager.getGroup(Game::groupproiectileleplayer1));
auto& proiectileleplayer2(manager.getGroup(Game::groupproiectileleplayer2));
auto& bonusuri(manager.getGroup(Game::groupBonusuri));
auto& viteza(manager.getGroup(Game::groupBonusViteza));

void Game::handleEvents()
{

	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		IsRunning = false;
		break;
	}
}
//reinitializeaza pozitiile si caracterisiticile playerilor in caz de replay si verifica coliziunile intamplate in timpul jocului
void Game::update()
{

	if (replay)
	{
		Game::ReInit();
	}
	else {
		SDL_Rect playerCol = player.getComponent<ComponentColiziune>().collider;
		Vector2D playerPos = player.getComponent<ComponentPozitie>().pozitie;
		SDL_Rect player2Col = player2.getComponent<ComponentColiziune>().collider;
		Vector2D player2Pos = player2.getComponent<ComponentPozitie>().pozitie;
		manager.refresh();
		manager.update();

		for (auto& c : colliders)
		{
			SDL_Rect pCol = c->getComponent<ComponentColiziune>().collider;
			if (TestColiziune::TestColiziuniInFunctieDePozitie(pCol, playerCol))
			{
				player.getComponent<ComponentPozitie>().pozitie = playerPos;
			}
			SDL_Rect eCol = c->getComponent<ComponentColiziune>().collider;
			if (TestColiziune::TestColiziuniInFunctieDePozitie(eCol, player2Col))
			{
				player2.getComponent<ComponentPozitie>().pozitie = player2Pos;
			}
		}
		for (auto& c : colliders)
		{
			c->getComponent<ComponentColiziune>().collider;
			for (auto& p : proiectileleplayer1)
				if (TestColiziune::TestColiziuniInFunctieDePozitie(c->getComponent<ComponentColiziune>().collider, p->getComponent<ComponentColiziune>().collider))
					p->destroy();
		}
		for (auto& c : colliders)
		{
			c->getComponent<ComponentColiziune>().collider;
			for (auto& p : proiectileleplayer2)
				if (TestColiziune::TestColiziuniInFunctieDePozitie(c->getComponent<ComponentColiziune>().collider, p->getComponent<ComponentColiziune>().collider))
					p->destroy();
		}
		for (auto& p : proiectileleplayer1)
		{
			if (TestColiziune::TestColiziuniInFunctieDePozitie(p->getComponent<ComponentColiziune>().collider, player2Col)) {
				std::cout << "player2 was hit!\n";
				startjoc = false;
				p1win = true;
			}
		}
		for (auto& p : proiectileleplayer2)
		{
			if (TestColiziune::TestColiziuniInFunctieDePozitie(p->getComponent<ComponentColiziune>().collider, playerCol)) {
				std::cout << "player1 was hit!\n";
				startjoc = false;
				p2win = true;
			}
		}
		for (auto& b : bonusuri)
		{
			if (TestColiziune::TestColiziuniInFunctieDePozitie(b->getComponent<ComponentColiziune>().collider, playerCol)) {
				player.getComponent<KeyboardController>().viteza2 = 2;
			}
			if (TestColiziune::TestColiziuniInFunctieDePozitie(b->getComponent<ComponentColiziune>().collider, player2Col)) {
				player2.getComponent<KeyboardControllerplayer2>().viteza1 = 2;
			}
		}
		for (auto& v : viteza)
		{
			if (TestColiziune::TestColiziuniInFunctieDePozitie(v->getComponent<ComponentColiziune>().collider, playerCol)) {
				player.getComponent<ComponentPozitie>().speed = 5;
			}
			if (TestColiziune::TestColiziuniInFunctieDePozitie(v->getComponent<ComponentColiziune>().collider, player2Col)) {
				player2.getComponent<ComponentPozitie>().speed = 5;
			}
		}
	}
}

void Game::draw()
{
	SDL_RenderClear(renderer);
	if (!startjoc && !p1win && !p2win)
	{
		Game::incarcareloadingscreen();
		Game::checkloadingplay();
	}
	if (startjoc && !p1win && !p2win)
	{
		SDL_RenderClear(renderer);
		for (auto& t : DesenMapa) {
			t->draw();
		}
		for (auto& c : colliders) {
			c->draw();
		}
		for (auto& p : players) {
			p->draw();
		}
		for (auto& p : proiectileleplayer1)
		{
			p->draw();
		}
		for (auto& p : proiectileleplayer2)
		{
			p->draw();
		}
	}

	if (p1win)
	{

		Game::incarcarewin1();
		Game::checkgotoloading();
	}
	if (p2win)
	{
		Game::incarcarewin2();
		Game::checkgotoloading();
	}
	SDL_RenderPresent(renderer);

}
//eliberare memorie
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_FreeMusic(player.getComponent<KeyboardController>().backgroundSoundS);
	Mix_FreeMusic(backgroundSound);
	Mix_FreeChunk(player.getComponent<KeyboardController>().shotEffect);
	Mix_FreeChunk(player2.getComponent<KeyboardControllerplayer2>().shotEffect);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::ReInit()
{

	p1win = false;
	p2win = false;
	replay = false;
	startjoc = false;
	reinit = true;

	player.getComponent<ComponentPozitie>().pozitie.x = 32;
	player.getComponent<ComponentPozitie>().pozitie.y = 32;
	player2.getComponent<ComponentPozitie>().pozitie.x = 1184;
	player2.getComponent<ComponentPozitie>().pozitie.y = 864;
	player.getComponent<ComponentPozitie>().speed = 4;
	player2.getComponent<ComponentPozitie>().speed = 4;
	player.getComponent<KeyboardController>().viteza2 = 1;
	player2.getComponent<KeyboardControllerplayer2>().viteza1 = 1;
	player.getComponent<ComponentPozitie>().viteza.x = 0;
	player.getComponent<ComponentPozitie>().viteza.y = 0;
	player2.getComponent<ComponentPozitie>().viteza.x = 0;
	player2.getComponent<ComponentPozitie>().viteza.y = 0;
}
//verifica pozitia mouse si momentul apasarii click stanga in drepturnghiurile dorite
void Game::checkloadingplay() {
	int x, y;
	Uint32 buttons;
	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);
	if (x >= 310 && x <= 660 && y >= 540 && y <= 700)
	{
		if ((buttons & SDL_BUTTON_LMASK) != 0)
		{
			startjoc = true;
		}
	}
	if (x >= 330 && x <= 635 && y >= 750 && y <= 900)
	{
		if ((buttons & SDL_BUTTON_LMASK) != 0)
		{
			IsRunning = false;
		}
	}
	if (x >= 15 && x <= 280 && y >= 655 && y <= 752)
	{
		if (Game::event.type == SDL_MOUSEBUTTONDOWN)
		{
			if ((buttons & SDL_BUTTON_LMASK) != 0)
			{
				if (Game::music)
				{
					//Mix_PlayMusic(Game::backgroundSound, -1);
					Game::music = false;
				}
				else {
					//Mix_PauseMusic();
					Game::music = true;
				}
			}
		}

	}
};

void Game::checkgotoloading() {
	int x, y;
	Uint32 buttons;
	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);
	if (x >= 825 && x <= 1220 && y >= 0 && y <= 385)
	{
		//std::cout << x << " " << y << "\n";
		if ((buttons & SDL_BUTTON_LMASK) != 0)
		{
			replay = true;
			std::cout << "Jocul a inceput de la capat\n";
		}
	}
	if (x >= 825 && x <= 1245 && y >= 470 && y <= 640)
	{
		if ((buttons & SDL_BUTTON_LMASK) != 0)
		{
			IsRunning = false;
		}
	}
};
//incarca imagine spefica loading/castigplayer1/castigplayer2
void Game::incarcareloadingscreen()
{
	SDL_RenderClear(renderer);
	ManagerTexturi::DrawTex(loading, { 0,0,1280,960 });
	SDL_RenderPresent(renderer);
}

void Game::incarcarewin1()
{
	SDL_RenderClear(renderer);
	ManagerTexturi::DrawTex(winp1, { 0,0,1280,960 });
	SDL_RenderPresent(renderer);
}

void Game::incarcarewin2()
{
	SDL_RenderClear(renderer);
	ManagerTexturi::DrawTex(winp2, { 0,0,1280,960 });
	SDL_RenderPresent(renderer);
}
//on/off muzica
void Game::PlayOrStopMusic()
{
	if (Game::on)
	{
		Mix_PlayMusic(Game::backgroundSound, -1);
		Game::on = false;
	}
	else {
		Mix_PauseMusic();
		Game::on = true;
	}
	Game::music = false;
}
