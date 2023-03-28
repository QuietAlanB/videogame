#ifndef TIMER_HH__
#define TIMER_HH__

#include <chrono>
#include <cstdint>

namespace core {

class timer {
private:
	std::chrono::time_point<std::chrono::system_clock> tp_start;
	std::chrono::time_point<std::chrono::system_clock> tp_prev_start;
	std::chrono::time_point<std::chrono::system_clock> tp_prev_end;
	uint64_t tick = 0;
public:
	unsigned max_tps;

	timer(unsigned max_tps);

	void start();
	void end();

	std::chrono::milliseconds last_delta() const;
	uint64_t current_tick() const;
	uint64_t elapsed_ticks() const;
};

}

#endif
