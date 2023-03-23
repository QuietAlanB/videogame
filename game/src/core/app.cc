#include "core/app.hh"

#include <SDL2/SDL.h>

app_request_mgr::app_request_mgr(app *app_) {
	this->app_ = app_;
	req_buf = std::queue<std::pair<request, response *>>();
}

void app_request_mgr::request_buffered(request req, response *resp) {
}

response app_request_mgr::request_now(request const &req) {
}

app::app(app_info const &info) {
	gfx = std::make_unique<graphics>(info.gfx.wnd_title, info.gfx.wnd_dims);
	kbd = std::make_unique<keyboard>();
	req_mgr = std::make_unique<app_request_mgr>(this);
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
	running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(e);
	}
}
