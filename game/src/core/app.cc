#include "core/app.hh"

#include <SDL2/SDL.h>

#include "core/comp/transform_comp.hh"
#include "core/comp/sprite_comp.hh"
#include "core/comp/dynamic_comp.hh"
#include "core/comp/aaboxcol_comp.hh"
#include "core/audio.hh"

namespace core {

app::app(app_info const &info) {
	gfx = std::make_shared<graphics>(info.gfx.wnd_title, info.gfx.wnd_dims);
	kbd = std::make_shared<keyboard>();
	world = std::make_shared<core::world>();
	timer = std::make_shared<core::timer>(info.timer.max_tps);

	iface.gfx = std::make_unique<graphics_iface>(gfx);
	iface.kbd = std::make_unique<keyboard_iface>(kbd);
	iface.world = std::make_unique<world_iface>(world, &iface);
	iface.timer = std::make_unique<timer_iface>(timer);
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
	std::filesystem::path bricks_path = "res/tex/bricks.bmp";
	texture_id smiley = iface.gfx->load_tex(smiley_path);
	texture_id bricks = iface.gfx->load_tex(bricks_path);

	auto go0 = std::make_shared<game_object>("smiley");
	auto trans0 = std::make_shared<transform_comp>(vec2(300.0f, 200.0f),
	                                               vec2(60.0f, 60.0f), 0.0f);
	auto sprite0 = std::make_shared<sprite_comp>(smiley);
	auto dynamic0 = std::make_shared<dynamic_comp>();
	auto aaboxcol0 = std::make_shared<aaboxcol_comp>(nullptr, nullptr, nullptr);

	auto go1 = std::make_shared<game_object>("bricks");
	auto trans1 = std::make_shared<transform_comp>(vec2(500.0f, 200.0f),
	                                               vec2(100.0f, 100.0f), 0.0f);
	auto sprite1 = std::make_shared<sprite_comp>(bricks);
	auto aaboxcol1 = std::make_shared<aaboxcol_comp>(nullptr, nullptr, nullptr);

	dynamic0->vel = vec2(2.8f, -5.8f);
	
	go0->add_comp(trans0);
	go0->add_comp(sprite0);
	go0->add_comp(dynamic0);
	go0->add_comp(aaboxcol0);

	go1->add_comp(trans1);
	go1->add_comp(sprite1);
	go1->add_comp(aaboxcol1);

	world->add_game_object(go0);
	world->add_game_object(go1);

	audio ad;
	sound_id num7_id = ad.snd_pool.load_sound("res/sfx/num7.wav");

	ad.snd_pool.play_sound(num7_id);

	running = true;
	while (running) {
		timer->start();

		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(e);

		iface.gfx->clear(70, 140, 240);

		world->update(iface);
		iface.gfx->present();

		timer->end();
	}
}

}
