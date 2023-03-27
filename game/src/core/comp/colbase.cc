#include "core/comp/colbase.hh"

#include <algorithm>

#include "util/log.hh"

namespace core {

std::optional<vec2> col_aabb_aabb(col_aabb const &me, col_aabb const &other,
                                  vec2 vel) {
	return std::nullopt;
}

}
