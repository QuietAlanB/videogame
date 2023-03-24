#include "core/iface/graphics_iface.hh"

namespace core {

graphics_iface::graphics_iface(std::shared_ptr<graphics> &gfx) {
	this->gfx = gfx;
}

texture_id graphics_iface::load_tex(std::filesystem::path const &path) {
	return gfx->tex_pool->load_texture(gfx->rend, path);
}

void graphics_iface::unload_tex(texture_id tex_id) {
	gfx->tex_pool->unload_texture(tex_id);
}

void graphics_iface::draw_tex(texture_id tex_id, int x, int y, int w, int h) {
	SDL_Rect dr = {x, y, w, h};
	SDL_RenderCopy(gfx->rend, gfx->tex_pool->get_texture(tex_id), nullptr, &dr);
}

void graphics_iface::clear(uint8_t r, uint8_t g, uint8_t b) {
	SDL_SetRenderDrawColor(gfx->rend, r, g, b, 255);
	SDL_RenderClear(gfx->rend);
}

void graphics_iface::present() {
	SDL_RenderPresent(gfx->rend);
}

}
