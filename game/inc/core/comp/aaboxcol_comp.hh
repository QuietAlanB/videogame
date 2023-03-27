#ifndef AABOXCOL_COMP_HH__
#define AABOXCOL_COMP_HH__

#include <cstdint>

#include "core/iface/iface.hh"
#include "core/world.hh"
#include "core/comp/colbase.hh"

namespace core {

class aaboxcol_comp : public component {
private:
	col_callback on_enter, on_stay, on_exit;
public:
	aaboxcol_comp(col_callback on_enter, col_callback on_stay,
	              col_callback on_exit);

	void on_update(game_object &go, iface &iface) override;
};

}

#endif
