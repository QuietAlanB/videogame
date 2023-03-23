#include "core/world.hh"

namespace core {

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

component_id game_object::add_comp(std::shared_ptr<component> comp) {
	comps.push_back(comp);
	return comps.size() - 1;
}

void game_object::set_comps_activity(std::string const &name, bool active) {
	for (std::shared_ptr<component> &comp : comps)
		if (name == typeid(*comp).name())
			comp->active = active;
}

void game_object::set_comp_activity(component_id comp_id, bool active) {
	comps[comp_id]->active = active;
}

void game_object::update(iface &iface) {
	for (std::shared_ptr<component> &comp : comps)
		if (comp->active)
			comp->on_update(*this, iface);
}

}
