#ifndef TIMER_IFACE_HH__
#define TIMER_IFACE_HH__

#include <memory>
#include <chrono>

#include "core/timer.hh"

namespace core {

class iface;

class timer_iface {
private:
	std::shared_ptr<core::timer> timer;
public:
	timer_iface(std::shared_ptr<core::timer> &timer);

	std::chrono::milliseconds delta_time();
};

};

#endif
