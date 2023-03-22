#include <utility>

#include <SDL2/SDL.h>

#include "core/app.hh"
#include "util/log.hh"

int main() {
	LOG("starting program...");
	SDL_Init(SDL_INIT_VIDEO);
	
	app_info info = {
		.gfx = {
			.wnd_dims = std::make_pair<int, int>(800, 600),
			.wnd_title = "hello world",
		},
	};
	
	app(info).run();
	
	SDL_Quit();
	LOG("exiting program...");
}
