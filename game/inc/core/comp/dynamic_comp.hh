#ifndef DYNAMIC_COMP_HH__
#define DYNAMIC_COMP_HH__

#include "core/world.hh"
#include "core/iface/iface.hh"
#include "util/vec2.hh"

namespace core {

#define GRAVITY_STRENGTH 0.12f

class dynamic_comp : public component {
public:
	vec2 vel, accel;
	bool gravity = true;

	void on_update(game_object &go, iface &iface) override;
};

}

#endif
