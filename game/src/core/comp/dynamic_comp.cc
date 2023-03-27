#include "core/comp/dynamic_comp.hh"

#include "core/comp/transform_comp.hh"

namespace core {

void dynamic_comp::on_update(game_object &go, iface &iface) {
	auto trans = go.get_comp<transform_comp>().value();

	vel += accel;
	if (gravity)
		vel.y += GRAVITY_STRENGTH;

	trans->pos += vel;
}

}
