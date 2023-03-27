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

	texture_id load_tex(std::filesystem::path const &path);
	void unload_tex(texture_id tex_id);
	void draw_point(int x, int y, uint8_t r, uint8_t g, uint8_t b, int size);
	void draw_tex(texture_id tex_id, int x, int y, int w, int h, float rot_deg);
	void draw_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);
	void fill_rect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);
	void clear(uint8_t r, uint8_t g, uint8_t b);
	void present();
};

}

#endif
