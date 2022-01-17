#include"Game.h"
Game* game = nullptr;

int main(int argc, char* argv[]) {

	const int fps = 60;
	const int frameDelay = 1000 / fps;

	Uint32 frameStart;
	int frameTime;

	game = new Game;
	game->init("War On The Sea", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, false);

	int a = -1;

	while (Game::IsRunning)
	{
		if (Game::music)
		{
			game->PlayOrStopMusic();
		}

		frameStart = SDL_GetTicks();

		game->handleEvents();

		game->update();
		game->draw();
		SDL_ShowCursor;
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}