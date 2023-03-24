#include "core/iface/world_iface.hh"

namespace core {

world_iface::world_iface(std::shared_ptr<core::world> &world,
                         core::iface *iface) {
	this->world = world;
	this->iface = iface;
}

}
