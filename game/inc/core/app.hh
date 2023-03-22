#ifndef APP_HH__
#define APP_HH__

#include <string>
#include <memory>
#include <utility>

#include "core/graphics.hh"
#include "core/keyboard.hh"

struct app_info {
	struct {
		std::pair<int, int> wnd_dims;
		std::string wnd_title;
	} gfx;
};

class app {
private:
	std::unique_ptr<graphics> gfx;
	std::unique_ptr<keyboard> kbd;
	bool running = false;
public:
	app(app_info const &info);

	void handle_event(SDL_Event const &e);
	void run();
};

#endif
