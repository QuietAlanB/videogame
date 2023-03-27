#include "core/iface/world_iface.hh"

namespace core {

world_iface::world_iface(std::shared_ptr<core::world> &world,
                         core::iface *iface) {
	this->world = world;
	this->iface = iface;
}

std::vector<std::shared_ptr<game_object>> world_iface::get_all_game_objects() {
	return world->game_objects;
}

std::optional<std::shared_ptr<game_object>>
world_iface::get_game_object(std::string const &name) {
	return world->get_game_object(name);
}

std::vector<std::shared_ptr<game_object>>
world_iface::get_game_objects(std::string const &name) {
	return world->get_game_objects(name);
}

void world_iface::add_game_object(std::shared_ptr<game_object> go) {
	world->add_game_object(go);
}

void world_iface::rm_game_object(std::shared_ptr<game_object> const &go) {
	world->rm_game_object(go);
}

void world_iface::rm_game_objects(std::string const &name) {
	world->rm_game_objects(name);
}

}
