#ifndef IFACE_HH__
#define IFACE_HH__

#include <memory>

#include "core/iface/graphics_iface.hh"
#include "core/iface/keyboard_iface.hh"
#include "core/iface/world_iface.hh"

namespace core {

class iface {
public:
	std::unique_ptr<graphics_iface> gfx;
	std::unique_ptr<keyboard_iface> kbd;
	std::unique_ptr<world_iface> world;
};

}

#endif
