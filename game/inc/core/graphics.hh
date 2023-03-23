#ifndef GRAPHICS_HH__
#define GRAPHICS_HH__

#include <string>
#include <utility>
#include <vector>
#include <filesystem>
#include <memory>
#include <cstdint>

#include <SDL2/SDL.h>

namespace core {

// tirimid: `texture_pool`s return an alias for `size_t` which indexes into the
// `pool` vector, allowing for the same texture to be stored in multiple places
// without having it be loaded multiple times.
// effectively a `SDL_Texture *` reference, but conceptually easier.
typedef size_t texture;

SDL_Texture *load_bmp(SDL_Renderer *rend, std::filesystem::path const &path);

class texture_pool {
private:
	std::vector<SDL_Texture *> pool;
	SDL_Texture *fallback_tex;
public:
	texture_pool(SDL_Renderer *rend);
	~texture_pool();

	texture load_texture(SDL_Renderer *rend, std::filesystem::path const &path);
	void unload_texture(texture tex_id);
	SDL_Texture *get_texture(texture tex_id);
};

class graphics {
public:
	SDL_Window *wnd;
	SDL_Renderer *rend;
	std::unique_ptr<texture_pool> tex_pool;

	graphics(std::string const &wnd_title, std::pair<int, int> wnd_dims);
	~graphics();
};

}

#endif
