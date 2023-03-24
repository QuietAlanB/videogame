#include "core/app.hh"

#include <SDL2/SDL.h>

#include "core/comp/transform_comp.hh"
#include "core/comp/sprite_comp.hh"

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

	auto go = std::make_shared<game_object>("smiley");
	auto trans = std::make_shared<transform_comp>(vec2(70.0f, 70.0f),
	                                              vec2(100.0f, 100.0f), 0.0f);
	auto sprite = std::make_shared<sprite_comp>(smiley);

	go->add_comp(std::static_pointer_cast<component>(trans));
	go->add_comp(std::static_pointer_cast<component>(sprite));

	world->add_game_object(go);

	running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(e);
		
		iface.gfx->clear(70, 140, 240);
		trans->pos.x += 0.01f;
		world->update(iface);
		iface.gfx->present();
	}
}

}
