#include "core/world.hh"

#include <algorithm>

namespace core {

game_object::game_object(std::string const &name) {
	this->name = name;
}

std::optional<std::shared_ptr<component>>
game_object::get_comp(std::string const &name) {
	for (std::shared_ptr<component> &comp : comps)
		if (name == typeid(*comp).name())
			return std::make_optional(comp);
	
	return std::nullopt;
}

std::vector<std::shared_ptr<component>>
game_object::get_comps(std::string const &name) {
	std::vector<std::shared_ptr<component>> mat_comps;
	
	for (std::shared_ptr<component> &comp : comps)
		if (name == typeid(*comp).name())
			mat_comps.push_back(comp);

	return mat_comps;
}

void game_object::add_comp(std::shared_ptr<component> comp) {
	comps.push_back(comp);
}

void game_object::rm_comp(std::shared_ptr<component> const &comp) {
	auto chk = [&](std::shared_ptr<component> const &go_comp) {
		return comp.get() == go_comp.get();
	};

	comps.erase(std::remove_if(comps.begin(), comps.end(), chk), comps.end());
}

void game_object::rm_comps(std::string const &name) {
	auto chk = [&](std::shared_ptr<component> const &comp) {
		return name == typeid(*comp).name();
	};

	comps.erase(std::remove_if(comps.begin(), comps.end(), chk), comps.end());
}

void game_object::update(iface &iface) {
	for (std::shared_ptr<component> &comp : comps)
		if (comp->active)
			comp->on_update(*this, iface);
}

std::optional<std::shared_ptr<game_object>>
world::get_game_object(std::string const &name) {
	for (std::shared_ptr<game_object> &go : game_objects)
		if (name == go->name)
			return std::make_optional(go);
	
	return std::nullopt;
}

std::vector<std::shared_ptr<game_object>>
world::get_game_objects(std::string const &name) {
	std::vector<std::shared_ptr<game_object>> mat_gos;
	
	for (std::shared_ptr<game_object> &go : game_objects)
		if (name == go->name)
			mat_gos.push_back(go);

	return mat_gos;
}

void world::add_game_object(std::shared_ptr<game_object> go) {
	game_objects.push_back(go);
}

void world::rm_game_object(std::shared_ptr<game_object> const &go) {
	auto chk = [&](std::shared_ptr<game_object> const &go_chk) {
		return go_chk.get() == go.get();
	};

	auto rm_if = std::remove_if(game_objects.begin(), game_objects.end(), chk);
	game_objects.erase(rm_if, game_objects.end());
}

void world::rm_game_objects(std::string const &name) {
	auto chk = [&](std::shared_ptr<game_object> const &go_chk) {
		return go_chk->name == name;
	};

	auto rm_if = std::remove_if(game_objects.begin(), game_objects.end(), chk);
	game_objects.erase(rm_if, game_objects.end());
}

void world::update(iface &iface) {
	for (std::shared_ptr<game_object> &go : game_objects)
		go->update(iface);
}

}
