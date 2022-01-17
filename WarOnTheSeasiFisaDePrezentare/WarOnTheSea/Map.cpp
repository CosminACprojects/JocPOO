#include"Map.h"
#include"Game.h"
#include<fstream>
#include"SistemEntitate-Component.h"
#include"ManagerDeComponente.h"

extern Manager manager;

Map::Map(std::string tID, int ms, int ts) :texID(tID), mapScale(ms), tileSize(ts) {}
Map::~Map() {}


void Map::LoadMap(std::string path, int sizeX, int sizeY) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int srcX, srcY;

	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++) {
			mapFile.get(c);
			srcY = atoi(&c) * tileSize;
			mapFile.get(c);
			srcX = atoi(&c) * tileSize;
			AddTile(srcX, srcY, x * (tileSize * mapScale), y * (tileSize * mapScale));
			mapFile.ignore();
		}
	}
	mapFile.ignore();
	for (int y = 0; y < sizeY; y++) {
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(c);
			if (c == '1') {
				auto& tcol(manager.addEntity());
				tcol.addComponent<ComponentColiziune>("harta", x * (tileSize * mapScale), y * (tileSize * mapScale), tileSize * mapScale);
				tcol.addGroup(Game::groupColliders);
			}
			if (c == '2')
			{
				auto& tbonus(manager.addEntity());
				tbonus.addComponent<ComponentColiziune>("harta", x * (tileSize * mapScale), y * (tileSize * mapScale), tileSize * mapScale);
				tbonus.addGroup(Game::groupBonusuri);
			}
			if (c == '3')
			{
				auto& vbonus(manager.addEntity());
				vbonus.addComponent<ComponentColiziune>("harta", x * (tileSize * mapScale), y * (tileSize * mapScale), tileSize * mapScale);
				vbonus.addGroup(Game::groupBonusViteza);
			}
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.addEntity());
	tile.addComponent<ComponentDesenMapa>(srcX, srcY, xpos, ypos, texID);
	tile.addGroup(Game::groupMap);
}
