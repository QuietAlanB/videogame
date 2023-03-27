#include "core/comp/sprite_comp.hh"

#include <memory>

#include "core/comp/transform_comp.hh"

namespace core {

sprite_comp::sprite_comp(texture_id tex_id) {
	this->tex_id = tex_id;
}

void sprite_comp::on_update(game_object &go, iface &iface) {
	auto trans = go.get_comp<transform_comp>().value();

	int x = static_cast<int>(trans->pos.x);
	int y = static_cast<int>(trans->pos.y);
	int w = static_cast<int>(trans->scale.x);
	int h = static_cast<int>(trans->scale.y);
	
	iface.gfx->draw_tex(tex_id, x, y, w, h, trans->rot);
}

}
