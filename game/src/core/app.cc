#include "core/app.hh"

#include <SDL2/SDL.h>

app::app(app_info const &info) {
	gfx = std::make_shared<graphics>(info.gfx.wnd_title, info.gfx.wnd_dims);
	kbd = std::make_shared<keyboard>();

	iface_.gfx = std::make_unique<graphics_iface>(gfx);
	iface_.kbd = std::make_unique<keyboard_iface>(kbd);
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
	texture smiley = iface_.gfx->load_tex(smiley_path);
	
	running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(e);

		iface_.gfx->clear(70, 140, 240);
		iface_.gfx->draw_tex(smiley, 100, 100, 300, 300);
		iface_.gfx->present();
	}
}
