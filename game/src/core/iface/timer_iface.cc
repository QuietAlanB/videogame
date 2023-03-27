#include "core/iface/timer_iface.hh"

namespace core {

timer_iface::timer_iface(std::shared_ptr<core::timer> &timer) {
	this->timer = timer;
}

std::chrono::milliseconds timer_iface::delta_time() {
	return timer->last_delta();
}

}
