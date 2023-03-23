#ifndef WORLD_HH__
#define WORLD_HH__

#include <vector>
#include <string>
#include <optional>
#include <memory>

namespace core {

typedef size_t component_id;

class iface;
class game_object;

// tirimid: when defining components for `game_object`s, inherit from this class
// add implement each of the virtual methods.
class component {
	bool active = true;
public:
	virtual void on_update(game_object &go, iface &iface);
	
	friend class game_object;
};

class game_object {
public:
	std::string name;
	std::vector<std::shared_ptr<component>> comps;

	// tirimid: here, `name` should be the literal name of the component as it
	// is defined in the code.
	// a component defined as `hello_comp` has a `name` of "hello_comp".
	// if a `game_object` has just one of a given component, use `get_comp()` -
	// otherwise, use `get_comps()`.
	std::optional<std::shared_ptr<component>> get_comp(std::string const &name);
	std::vector<std::shared_ptr<component>> get_comps(std::string const &name);

	component_id add_comp(std::shared_ptr<component> comp);
	void set_comps_activity(std::string const &name, bool active);
	void set_comp_activity(component_id comp_id, bool active);

	void update(iface &iface);
};

class world {
private:
	std::vector<game_object> game_objects;
public:
	void update(iface &iface);
};

}

#endif
