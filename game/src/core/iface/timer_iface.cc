#include "core/iface/timer_iface.hh"

namespace core {

timer_iface::timer_iface(std::shared_ptr<core::timer> &timer) {
	this->timer = timer;
}

std::chrono::milliseconds timer_iface::delta_time() const {
	return timer->last_delta();
}

uint64_t timer_iface::current_tick() const {
	return timer->current_tick();
}

uint64_t timer_iface::elapsed_ticks() const {
	return timer->elapsed_ticks();
}

}
