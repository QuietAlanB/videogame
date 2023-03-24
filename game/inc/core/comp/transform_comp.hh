#ifndef TRANSFORM_COMP_HH__
#define TRANSFORM_COMP_HH__

#include "core/iface/iface.hh"
#include "core/world.hh"
#include "util/vec2.hh"

namespace core {

class transform_comp : public component {
public:
	vec2 pos, scale;
	float rot;
	
	transform_comp();
	transform_comp(vec2 const &pos, vec2 const &scale, float rot);
	
	void on_update(game_object &go, iface &iface) override;
};

}

#endif
