#include "core/world.hh"

#include <algorithm>

template<typename T, typename F>
static std::optional<T> get_if_exists(std::vector<T> &v, F const &cmp) {
	for (T &i : v)
		if (cmp(i))
			return std::make_optional(i);
	
	return std::nullopt;
}

template<typename T, typename F>
static std::vector<T> get_all(std::vector<T> &v, F const &cmp) {
	std::vector<T> mat;

	for (T &i : v)
		if (cmp(i))
			mat.push_back(i);

	return mat;
}

template<typename T, typename F>
static void rm_all_by_cmp(std::vector<T> &v, F const &cmp) {
	v.erase(std::remove_if(v.begin(), v.end(), cmp), v.end());
}

template<typename T>
static void rm_by_ptr_cmp(std::vector<std::shared_ptr<T>> &v,
                          std::shared_ptr<T> const &ptr) {
	auto cmp = [&](std::shared_ptr<T> const &other_ptr) {
		return ptr.get() == other_ptr.get();
	};

	rm_all_by_cmp(v, cmp);
}

namespace core {

game_object::game_object(std::string const &name) {
	this->name = name;
}

std::optional<std::shared_ptr<component>>
game_object::get_comp(std::string const &name) {
	auto cmp = [&](std::shared_ptr<component> const &comp) {
		return name == typeid(*comp).name();
	};

	return get_if_exists(comps, cmp);
}

std::vector<std::shared_ptr<component>>
game_object::get_comps(std::string const &name) {
	auto cmp = [&](std::shared_ptr<component> const &comp) {
		return name == typeid(*comp).name();
	};
	
	return get_all(comps, cmp);
}

void game_object::add_comp(std::shared_ptr<component> comp) {
	comps.push_back(comp);
}

void game_object::rm_comp(std::shared_ptr<component> const &comp) {
	rm_by_ptr_cmp(comps, comp);
}

void game_object::rm_comps(std::string const &name) {
	auto cmp = [&](std::shared_ptr<component> const &comp) {
		return name == typeid(*comp).name();
	};

	rm_all_by_cmp(comps, cmp);
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
