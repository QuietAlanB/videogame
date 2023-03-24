#include "core/app.hh"

#include <SDL2/SDL.h>

namespace core {

app::app(app_info const &info) {
	gfx = std::make_shared<graphics>(info.gfx.wnd_title, info.gfx.wnd_dims);
	kbd = std::make_shared<keyboard>();
	world = std::make_shared<core::world>();

	iface.gfx = std::make_unique<graphics_iface>(gfx);
	iface.kbd = std::make_unique<keyboard_iface>(kbd);
	iface.world = std::make_unique<world_iface>(world, &iface);
}

void app::handle_event(SDL_Event const &e) {
	switch (e.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_KEYDOWN:
		kbd->set_key_state(e.key.keysym.sym, true);
		break;
	case SDL_KEYUP:
		kbd->set_key_state(e.key.keysym.sym, false);
		break;
	}
}

void app::run() {
	std::filesystem::path smiley_path = "res/tex/smiley.bmp";
	texture_id smiley = iface.gfx->load_tex(smiley_path);
	
	running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(e);

		iface.gfx->clear(70, 140, 240);
		iface.gfx->draw_tex(smiley, 100, 100, 300, 300);
		iface.gfx->present();
	}
}

}
