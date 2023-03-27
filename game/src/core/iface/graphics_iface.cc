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

void graphics_iface::draw_point(int x, int y, uint8_t r, uint8_t g, uint8_t b,
                                int size) {
	SDL_Rect rct = {x - size / 2, y - size / 2, size, size};
	SDL_SetRenderDrawColor(gfx->rend, r, g, b, 255);
	SDL_RenderFillRect(gfx->rend, &rct);
}

void graphics_iface::draw_tex(texture_id tex_id, int x, int y, int w, int h,
                              float rot_deg) {
	SDL_Rect dr = {x - w / 2, y - h / 2, w, h};
	SDL_RenderCopyEx(gfx->rend, gfx->tex_pool->get_texture(tex_id), nullptr,
	                 &dr, rot_deg, nullptr, SDL_FLIP_NONE);
}

void graphics_iface::draw_rect(int x, int y, int w, int h, uint8_t r, uint8_t g,
                               uint8_t b) {
	SDL_Rect rct = {x - w / 2, y - h / 2, w, h};
	SDL_SetRenderDrawColor(gfx->rend, r, g, b, 255);
	SDL_RenderDrawRect(gfx->rend, &rct);
}

void graphics_iface::fill_rect(int x, int y, int w, int h, uint8_t r, uint8_t g,
                               uint8_t b) {
	SDL_Rect rct = {x - w / 2, y - h / 2, w, h};
	SDL_SetRenderDrawColor(gfx->rend, r, g, b, 255);
	SDL_RenderFillRect(gfx->rend, &rct);
}

void graphics_iface::clear(uint8_t r, uint8_t g, uint8_t b) {
	SDL_SetRenderDrawColor(gfx->rend, r, g, b, 255);
	SDL_RenderClear(gfx->rend);
}

void graphics_iface::present() {
	SDL_RenderPresent(gfx->rend);
}

}
