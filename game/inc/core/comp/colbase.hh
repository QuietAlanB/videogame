#ifndef COLBASE_HH__
#define COLBASE_HH__

#include <vector>
#include <memory>
#include <optional>

#include "core/iface/iface.hh"
#include "core/world.hh"
#include "util/vec2.hh"
#include "core/comp/transform_comp.hh"

namespace core {

// tirimid: collision callback type.
// the first argument determines the object which detected a collision, the
// second argument determines the object it collided with.
typedef bool (*col_callback)(game_object &, game_object &, iface &);

struct col_aabb {
	float x, y, w, h;
};

struct col_circle {
	float x, y, r;
};

struct col_cvxshape {
	float x, y;
	std::vector<vec2> const &verts;
};

// tirimid: collision detection functions return the position to which `me` must
// be moved in order to resolve the collision, or `std::nullopt` if one didn't
// occur in the first place.
std::optional<vec2> col_aabb_aabb(col_aabb const &me, col_aabb const &other,
                                  vec2 vel);

}

#endif
