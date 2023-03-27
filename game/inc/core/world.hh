#ifndef WORLD_HH__
#define WORLD_HH__

#include <vector>
#include <string>
#include <optional>
#include <memory>

#include "util/vectorutil.hh"

namespace core {

class iface;
class game_object;
class world_iface;

// tirimid: when defining components for `game_object`s, inherit from this class
// add implement each of the virtual methods.
class component {
public:
	bool active = true;

	virtual void on_update(game_object &go, iface &iface) = 0;
};

class game_object {
private:
	std::vector<std::shared_ptr<component>> comps;
public:
	std::string name;
	
	game_object(std::string const &name);
	
	// tirimid: if a `game_object` has just one of a given component, use
	// `get_comp()` - otherwise, use `get_comps()`.
	template<typename T>
	std::optional<std::shared_ptr<T>> get_comp() {
		auto cmp = [](std::shared_ptr<component> const &comp) {
			return typeid(T) == typeid(*comp);
		};
		
		auto comp = get_if_exists(comps, cmp);
		if (!comp.has_value())
			return std::nullopt;

		return std::make_optional(std::dynamic_pointer_cast<T>(comp.value()));
	}

	template<typename T>
	std::vector<std::shared_ptr<T>> get_comps() {
		auto cmp = [](std::shared_ptr<component> const &comp) {
			return typeid(T) == typeid(*comp);
		};
		
		auto comps = get_all(comps, cmp);
		std::vector<std::shared_ptr<T>> casted_comps;
		for (std::shared_ptr<component> &comp : comps)
			casted_comps.push_back(std::dynamic_pointer_cast<T>(comp));

		return casted_comps;
	}

	template<typename T>
	void add_comp(std::shared_ptr<T> const &comp) {
		auto actual_comp = std::static_pointer_cast<component>(comp);
		comps.push_back(actual_comp);
	}

	template<typename T>
	void rm_comp(std::shared_ptr<T> const &comp) {
		auto actual_comp = std::static_pointer_cast<component>(comp);
		rm_by_ptr_cmp(comps, actual_comp);
	}

	template<typename T>
	void rm_comps() {
		auto cmp = [](std::shared_ptr<component> const &comp) {
			return typeid(T) == typeid(*comp);
		};

		rm_all_by_cmp(comps, cmp);
	}
	
	void update(iface &iface);

	friend class world;
};

class world {
public:
	std::vector<std::shared_ptr<game_object>> game_objects;
	
	std::optional<std::shared_ptr<game_object>>
	get_game_object(std::string const &name);

	std::vector<std::shared_ptr<game_object>>
	get_game_objects(std::string const &name);

	void add_game_object(std::shared_ptr<game_object> const &go);
	void rm_game_object(std::shared_ptr<game_object> const &go);
	void rm_game_objects(std::string const &name);
	void update(iface &iface);
};

}

#endif
