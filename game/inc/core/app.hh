#ifndef APP_HH__
#define APP_HH__

#include <string>
#include <memory>
#include <utility>
#include <queue>

#include "core/graphics.hh"
#include "core/keyboard.hh"
#include "core/request.hh"

struct app_info {
	struct {
		std::pair<int, int> wnd_dims;
		std::string wnd_title;
	} gfx;
};

class app;

// tirmid: when running, all loaded objects in the current world are updated
// with a reference to an `app_request_mgr`.
// this exposes a request-based interface to the `app` for which it manages
// requests, allowing a potential increase in efficiency and a simpler method of
// interacting with the underlying `app` from a world object.
class app_request_mgr {
private:
	app *app_;
	std::queue<std::pair<request, response *>> req_buf;
public:
	app_request_mgr(app *app_);

	// tirimid: if `request_buffered()` is called with `out_resp` set to
	// `nullptr`, the response will be discarded and not written.
	// use this if you know that a buffered request is very unlikely to fail and
	// does not need to be checked.
	void request_buffered(request req, response *resp);
	response request_now(request const &req);
};

class app {
private:
	std::unique_ptr<graphics> gfx;
	std::unique_ptr<keyboard> kbd;
	std::unique_ptr<app_request_mgr> req_mgr;
	bool running = false;
public:
	friend class app_request_mgr;
	
	app(app_info const &info);

	void handle_event(SDL_Event const &e);
	void run();
};

#endif
