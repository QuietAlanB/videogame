#include "core/graphics.hh"

#include "util/log.hh"

// tirimid: whenever a texture is unloaded, but the ID of that texture is still
// in use, `texture_pool` will resort to giving a fallback texture when the
// original, now-unloaded, texture is requested.
#define FALLBACK_TEX_PATH "res/tex/default.bmp"

namespace core {

SDL_Texture *load_bmp(SDL_Renderer *rend, std::filesystem::path const &path) {
	SDL_Surface *surf = SDL_LoadBMP(path.string().c_str());
	if (surf == nullptr)
		ERROR("failed to load bmp: " + path.string());
	
	SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surf);
	SDL_FreeSurface(surf);
	return tex;
}

texture_pool::texture_pool(SDL_Renderer *rend) {
	pool = std::vector<SDL_Texture *>();
	fallback_tex = load_bmp(rend, FALLBACK_TEX_PATH);
}

texture_pool::~texture_pool() {
	SDL_DestroyTexture(fallback_tex);
	for (SDL_Texture *tex : pool)
		if (tex != fallback_tex)
			SDL_DestroyTexture(tex);
}

texture texture_pool::load_texture(SDL_Renderer *rend,
                                  std::filesystem::path const &path) {
	pool.push_back(load_bmp(rend, path));
	return pool.size() - 1;
}

void texture_pool::unload_texture(texture tex_id) {
	SDL_DestroyTexture(pool[tex_id]);
	pool[tex_id] = fallback_tex;
}

SDL_Texture *texture_pool::get_texture(texture tex_id) {
	return pool[tex_id];
}

graphics::graphics(std::string const &wnd_title, std::pair<int, int> wnd_dims) {
	wnd = SDL_CreateWindow(wnd_title.c_str(), SDL_WINDOWPOS_UNDEFINED,
	                       SDL_WINDOWPOS_UNDEFINED, wnd_dims.first,
	                       wnd_dims.second, 0);
	
	if (wnd == nullptr)
		ERROR("could not create window: " + wnd_title);

	rend = SDL_CreateRenderer(wnd, -1, SDL_RENDERER_ACCELERATED);
	if (rend == nullptr)
		ERROR("could not create renderer for window: " + wnd_title);

	tex_pool = std::make_unique<texture_pool>(rend);
}

graphics::~graphics() {
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(wnd);
}

}
