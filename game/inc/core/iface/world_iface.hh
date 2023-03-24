#ifndef WORLD_IFACE_HH__
#define WORLD_IFACE_HH__

#include <memory>

#include "core/world.hh"

namespace core {

class iface;

class world_iface {
private:
	std::shared_ptr<core::world> world;
	core::iface *iface;
public:
	world_iface(std::shared_ptr<core::world> &world, core::iface *iface);
};

}

#endif
