#ifndef TRANSFORM_COMP_HH__
#define TRANSFORM_COMP_HH__

#include "core/iface/iface.hh"
#include "core/world.hh"
#include "util/vec2.hh"
#include "util/mat2.hh"

namespace core {

class transform_comp : public component {
public:
	vec2 pos, scale;

	// tirimid: for ease of use and compatibility with SDL2, store rotation in
	// degrees - NOT in radians.
	float rot;
	
	transform_comp();
	transform_comp(vec2 const &pos, vec2 const &scale, float rot);
	
	void on_update(game_object &go, iface &iface) override;
	vec2 transform_point_rel(vec2 const &p);
};

}

#endif
