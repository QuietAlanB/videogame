#include "core/timer.hh"

#include <cstdint>

#include <SDL2/SDL.h>

namespace core {

timer::timer(unsigned max_tps) {
	this->max_tps = max_tps;
	tp_start = tp_prev_start = tp_prev_end = std::chrono::system_clock::now();
}

void timer::start() {
	tp_start = std::chrono::system_clock::now();
	++tick;
}

void timer::end() {
	auto end = std::chrono::system_clock::now();
	tp_prev_start = tp_start;
	tp_prev_end = end;

	auto dur = end - tp_start;
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
	double delay = 1000.0 / static_cast<double>(max_tps);
	delay -= delay - ms.count() > 0.0 ? ms.count() : 0.0;
	SDL_Delay(static_cast<uint32_t>(delay));
}

std::chrono::milliseconds timer::last_delta() const {
	auto dur = tp_prev_end - tp_prev_start;
	return std::chrono::duration_cast<std::chrono::milliseconds>(dur);
}

uint64_t timer::current_tick() const {
	return tick;
}

uint64_t timer::elapsed_ticks() const {
	return tick == 0 ? 0 : tick - 1;
}

}
