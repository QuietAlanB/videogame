#ifndef WORLD_HH__
#define WORLD_HH__

#include <vector>
#include <string>
#include <optional>
#include <memory>

namespace core {

class iface;
class game_object;

// tirimid: when defining components for `game_object`s, inherit from this class
// add implement each of the virtual methods.
class component {
public:
	bool active = true;

	virtual void on_update(game_object &go, iface &iface);
};

class game_object {
private:
	std::vector<std::shared_ptr<component>> comps;
	std::string name;
public:
	game_object(std::string const &name);
	
	// tirimid: here, `name` should be the literal name of the component as it
	// is defined in the code.
	// a component defined as `hello_comp` has a `name` of "hello_comp".
	// if a `game_object` has just one of a given component, use `get_comp()` -
	// otherwise, use `get_comps()`.
	std::optional<std::shared_ptr<component>> get_comp(std::string const &name);
	std::vector<std::shared_ptr<component>> get_comps(std::string const &name);
	
	void add_comp(std::shared_ptr<component> comp);
	void rm_comp(std::shared_ptr<component> const &comp);
	void rm_comps(std::string const &name);
	void update(iface &iface);

	friend class world;
};

class world {
private:
	std::vector<std::shared_ptr<game_object>> game_objects;
public:
	std::optional<std::shared_ptr<game_object>>
	get_game_object(std::string const &name);

	std::vector<std::shared_ptr<game_object>>
	get_game_objects(std::string const &name);

	void add_game_object(std::shared_ptr<game_object> go);
	void rm_game_object(std::shared_ptr<game_object> const &go);
	void rm_game_objects(std::string const &name);
	void update(iface &iface);
};

}

#endif
