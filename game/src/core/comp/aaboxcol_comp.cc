#include "core/comp/aaboxcol_comp.hh"

#include <vector>
#include <algorithm>
#include <memory>
#include <string>

#include "util/vectorutil.hh"
#include "util/log.hh"

namespace core {

aaboxcol_comp::aaboxcol_comp(col_callback on_enter, col_callback on_stay,
                             col_callback on_exit) {
	this->on_enter = on_enter;
	this->on_stay = on_stay;
	this->on_exit = on_exit;
}

void aaboxcol_comp::on_update(game_object &go, iface &iface) {
}

}
