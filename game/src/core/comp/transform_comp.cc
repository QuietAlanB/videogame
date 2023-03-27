#include "core/comp/transform_comp.hh"

#include <cmath>
#include <numbers>

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

vec2 transform_comp::transform_point_rel(vec2 const &p) {
	float rot_rad = rot * std::numbers::pi / 180.0f;
	mat2 scale_mat(scale.x, 0.0f, 0.0f, scale.y);
	mat2 rot_mat(cos(rot_rad), -sin(rot_rad), sin(rot_rad), cos(rot_rad));
	vec2 trans_p = p;
	trans_p = scale_mat * trans_p;
	trans_p = rot_mat * trans_p;
	trans_p += pos;
	return trans_p;
}

}
