#ifndef KEYBOARD_HH__
#define KEYBOARD_HH__

#include <cstdint>
#include <vector>
#include <memory>

#include <SDL2/SDL.h>

namespace core {

#define MAX_KEY_AXIS_KEYCODES 4

// tirimid: upon creation of `keyboard`, the horizontal and vertical axes are
// automatically registered as axis IDs 0 and 1.
// use these macros to access them in a convenient way without having to store
// any information regarding key axis IDs.
#define KEY_AXIS_HORIZONTAL 0
#define KEY_AXIS_VERTICAL 1

typedef size_t key_axis_id;

struct key_axis {
	SDL_Keycode pos[MAX_KEY_AXIS_KEYCODES], neg[MAX_KEY_AXIS_KEYCODES];
};

class keyboard {
private:
	std::vector<key_axis> axes;
	uint8_t key_states[0x21b / 8] = {0};
public:
	keyboard();
	
	void set_key_state(SDL_Keycode kc, bool state);
	bool is_pressed(SDL_Keycode kc) const;
	key_axis_id add_axis(key_axis const &axis);
	int axis_value(key_axis_id id) const;
};

}

#endif
