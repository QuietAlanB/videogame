#include "core/keyboard.hh"

keyboard::keyboard() {
	axes = std::vector<key_axis>();

	key_axis ka_horiz = {
		.pos = {SDLK_RIGHT},
		.neg = {SDLK_LEFT},
	};

	key_axis ka_vert = {
		.pos = {SDLK_UP},
		.neg = {SDLK_DOWN},
	};

	add_axis(ka_horiz);
	add_axis(ka_vert);
}

void keyboard::set_key_state(SDL_Keycode kc, bool state) {
	if ((kc & 1 << 30) > 0) {
		kc &= ~(1 << 30);
		kc += 0x100;
	}

	key_states[kc / 8] &= ~(1 << kc % 8);
	key_states[kc / 8] |= state << kc % 8;
}

bool keyboard::is_pressed(SDL_Keycode kc) const {
	if ((kc & 1 << 30) > 0) {
		kc &= ~(1 << 30);
		kc += 0x100;
	}

	return (key_states[kc / 8] & 1 << kc % 8) > 0;
}

key_axis_id keyboard::add_axis(key_axis const &axis) {
	axes.push_back(axis);
	return axes.size() - 1;
}

int keyboard::axis_value(key_axis_id id) const {
	int val = 0;
	
	for (size_t i = 0; i < MAX_KEY_AXIS_KEYCODES; ++i)
		if (is_pressed(axes[id].pos[i])) {
			++val;
			break;
		}

	for (size_t i = 0; i < MAX_KEY_AXIS_KEYCODES; ++i)
		if (is_pressed(axes[id].neg[i])) {
			--val;
			break;
		}

	return val;
}
