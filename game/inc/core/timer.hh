#ifndef TIMER_HH__
#define TIMER_HH__

#include <chrono>

namespace core {

class timer {
private:
	std::chrono::time_point<std::chrono::system_clock> tp_start;
	std::chrono::time_point<std::chrono::system_clock> tp_prev_start;
	std::chrono::time_point<std::chrono::system_clock> tp_prev_end;
public:
	unsigned max_tps;

	timer(unsigned max_tps);

	void start();
	void end();

	std::chrono::milliseconds last_delta();
};

}

#endif
