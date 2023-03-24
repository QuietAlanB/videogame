#include "core/comp/transform_comp.hh"

namespace core {

transform_comp::transform_comp() {
	pos = vec2(0.0f);
	scale = vec2(1.0f);
	rot = 0.0f;
}

transform_comp::transform_comp(vec2 const &pos, vec2 const &scale, float rot) {
	this->pos = pos;
	this->scale = scale;
	this->rot = rot;
}

void transform_comp::on_update(game_object &go, iface &iface) {
}

}
