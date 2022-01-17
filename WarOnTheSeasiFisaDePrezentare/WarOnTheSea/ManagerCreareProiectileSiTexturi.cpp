#include"ManagerCreareProiectileSiTexturi.h"
#include"ManagerDeComponente.h"
ManagerCreareProiectileSiTexturi::ManagerCreareProiectileSiTexturi(Manager* man) :manager(man)
{}

ManagerCreareProiectileSiTexturi::~ManagerCreareProiectileSiTexturi()
{}

void ManagerCreareProiectileSiTexturi::CreateProjectileplayer1(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<ComponentPozitie>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<ComponentImagine>(id);
	projectile.addComponent<ComponentProiectil>(range, speed, vel);
	projectile.addComponent<ComponentColiziune>("projectile1");
	projectile.addGroup(Game::groupproiectileleplayer1);
}
void ManagerCreareProiectileSiTexturi::CreateProjectileplayer2(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<ComponentPozitie>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<ComponentImagine>(id);
	projectile.addComponent<ComponentProiectil>(range, speed, vel);
	projectile.addComponent<ComponentColiziune>("projectile2");
	projectile.addGroup(Game::groupproiectileleplayer2);
}
void ManagerCreareProiectileSiTexturi::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, ManagerTexturi::LoadTexture(path));
}

SDL_Texture* ManagerCreareProiectileSiTexturi::GetTexture(std::string id)
{
	return textures[id];
}