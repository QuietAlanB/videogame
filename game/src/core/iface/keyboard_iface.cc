#include "core/iface/keyboard_iface.hh"

keyboard_iface::keyboard_iface(std::shared_ptr<keyboard> &kbd) {
	this->kbd = kbd;
}

bool keyboard_iface::is_pressed(SDL_Keycode kc) const {
	return kbd->is_pressed(kc);
}

key_axis_id keyboard_iface::add_axis(key_axis const &axis) {
	return kbd->add_axis(axis);
}

int keyboard_iface::axis_value(key_axis_id id) const {
	return kbd->axis_value(id);
}
