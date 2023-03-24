#include "core/world.hh"

namespace core {

game_object::game_object(std::string const &name) {
	this->name = name;
}

void game_object::add_comp(std::shared_ptr<component> comp) {
	comps.push_back(comp);
}

void game_object::rm_comp(std::shared_ptr<component> const &comp) {
	rm_by_ptr_cmp(comps, comp);
}

void game_object::update(iface &iface) {
	for (std::shared_ptr<component> &comp : comps)
		if (comp->active)
			comp->on_update(*this, iface);
}

std::optional<std::shared_ptr<game_object>>
world::get_game_object(std::string const &name) {
	auto cmp = [&](std::shared_ptr<game_object> const &go) {
		return name == go->name;
	};
	
	return get_if_exists(game_objects, cmp);
}

std::vector<std::shared_ptr<game_object>>
world::get_game_objects(std::string const &name) {
	auto cmp = [&](std::shared_ptr<game_object> const &go) {
		return name == go->name;
	};

	return get_all(game_objects, cmp);
}

void world::add_game_object(std::shared_ptr<game_object> go) {
	game_objects.push_back(go);
}

void world::rm_game_object(std::shared_ptr<game_object> const &go) {
	rm_by_ptr_cmp(game_objects, go);
}

void world::rm_game_objects(std::string const &name) {
	auto cmp = [&](std::shared_ptr<game_object> const &go_chk) {
		return go_chk->name == name;
	};

	rm_all_by_cmp(game_objects, cmp);
}

void world::update(iface &iface) {
	for (std::shared_ptr<game_object> &go : game_objects)
		go->update(iface);
}

}
