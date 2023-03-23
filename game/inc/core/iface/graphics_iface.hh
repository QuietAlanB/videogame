#ifndef GRAPHICS_IFACE_HH__
#define GRAPHICS_IFACE_HH__

#include <memory>

#include "core/graphics.hh"

namespace core {

class graphics_iface {
private:
	std::shared_ptr<graphics> gfx;
public:
	graphics_iface(std::shared_ptr<graphics> &gfx);

	texture load_tex(std::filesystem::path const &path);
	void unload_tex(texture tex_id);
	void draw_tex(texture tex_id, int x, int y, int w, int h);
	void clear(uint8_t r, uint8_t g, uint8_t b);
	void present();
};

}

#endif
