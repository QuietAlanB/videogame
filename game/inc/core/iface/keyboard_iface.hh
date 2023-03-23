#ifndef KEYBOARD_IFACE_HH__
#define KEYBOARD_IFACE_HH__

#include <memory>

#include "core/keyboard.hh"

class keyboard_iface {
private:
	std::shared_ptr<keyboard> kbd;
public:
	keyboard_iface(std::shared_ptr<keyboard> &kbd);

	bool is_pressed(SDL_Keycode kc) const;
	key_axis_id add_axis(key_axis const &axis);
	int axis_value(key_axis_id id) const;
};

#endif
