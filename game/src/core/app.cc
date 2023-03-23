#include "core/app.hh"

#include <SDL2/SDL.h>

app_request_mgr::app_request_mgr(app *app_) {
	this->app_ = app_;
	req_buf = std::queue<std::pair<request, response *>>();
}

void app_request_mgr::request_buffered(request req, response *resp) {
	req_buf.push(std::make_pair(req, resp));
}

response app_request_mgr::request_now(request const &req) {
	response resp = {
		.type = req.type,
	};
	
	switch (req.type) {
	case request_type::gfx_present:
		SDL_RenderPresent(app_->gfx->rend);
		break;
	case request_type::gfx_clear: {
		SDL_SetRenderDrawColor(app_->gfx->rend, req.gfx_clear.r,
		                       req.gfx_clear.g, req.gfx_clear.b, 255);
		SDL_RenderClear(app_->gfx->rend);
		break;
	}
	case request_type::gfx_draw_tex: {
		SDL_Rect draw_rect = {
			.x = req.gfx_draw_tex.x,
			.y = req.gfx_draw_tex.y,
			.w = req.gfx_draw_tex.w,
			.h = req.gfx_draw_tex.h,
		};

		texture tex_id = req.gfx_draw_tex.tex_id;
		SDL_Texture *tex = app_->gfx->tex_pool->get_texture(tex_id);
		SDL_RenderCopy(app_->gfx->rend, tex, nullptr, &draw_rect);
		break;
	}
	}

	return resp;
}

void app_request_mgr::flush_req_buf() {
	while (!req_buf.empty()) {
		std::pair<request, response *> rrpair = req_buf.front();
		req_buf.pop();
		response resp = request_now(rrpair.first);
		if (rrpair.second != nullptr)
			*rrpair.second = resp;
	}
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
	std::filesystem::path smiley_path = "res/tex/smiley.bmp";
	texture smiley = gfx->tex_pool->load_texture(gfx->rend, smiley_path);
	
	running = true;
	while (running) {
		SDL_Event e;
		while (SDL_PollEvent(&e))
			handle_event(e);

		request clear = {
			.type = request_type::gfx_clear,
			.gfx_clear = {
				.r = 100,
				.g = 150,
				.b = 240,
			},
		};

		request draw_tex = {
			.type = request_type::gfx_draw_tex,
			.gfx_draw_tex = {
				.x = 200,
				.y = 100,
				.w = 200,
				.h = 200,
				.tex_id = smiley,
			},
		};

		request present = {
			.type = request_type::gfx_present,
		};

		req_mgr->request_buffered(clear, nullptr);
		req_mgr->request_buffered(draw_tex, nullptr);
		req_mgr->request_buffered(present, nullptr);

		req_mgr->flush_req_buf();
	}
}
