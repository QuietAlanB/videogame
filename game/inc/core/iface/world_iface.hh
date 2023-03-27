#ifndef WORLD_IFACE_HH__
#define WORLD_IFACE_HH__

#include <memory>
#include <string>
#include <optional>
#include <algorithm>

#include "core/world.hh"
#include "util/vectorutil.hh"

namespace core {

class iface;

class world_iface {
private:
	std::shared_ptr<core::world> world;
	core::iface *iface;
public:
	world_iface(std::shared_ptr<core::world> &world, core::iface *iface);
	
	std::vector<std::shared_ptr<game_object>> get_all_game_objects();
	
	std::optional<std::shared_ptr<game_object>>
	get_game_object(std::string const &name);
	
	std::vector<std::shared_ptr<game_object>>
	get_game_objects(std::string const &name);

	template<typename T>
	std::vector<std::shared_ptr<game_object>> get_game_objects_with() {
		auto no_comp = [](std::shared_ptr<game_object> const &go) {
			return !go->get_comp<T>().has_value();
		};

		auto gos = world->game_objects;
		gos.erase(std::remove_if(gos.begin(), gos.end(), no_comp), gos.end());
		return gos;
	}

	void add_game_object(std::shared_ptr<game_object> go);
	void rm_game_object(std::shared_ptr<game_object> const &go);
	void rm_game_objects(std::string const &name);
};

}

#endif
