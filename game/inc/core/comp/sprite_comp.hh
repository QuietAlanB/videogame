#ifndef SPRITE_COMP_HH__
#define SPRITE_COMP_HH__

#include <filesystem>

#include "core/iface/iface.hh"
#include "core/world.hh"
#include "core/graphics.hh"

namespace core {

class sprite_comp : public component {
private:
	texture_id tex_id;
public:
	sprite_comp(texture_id tex_id);

	void on_update(game_object &go, iface &iface) override;
};

}

#endif
