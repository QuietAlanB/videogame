#ifndef REQUEST_HH__
#define REQUEST_HH__

#include "core/graphics.hh"

union request {
	struct {
		int x, y, w, h;
		texture tex_id;
	} gfx_draw_tex;
};

// tirimid: the `status` field of each response designates a "return code" of
// sorts for the given request.
// unless specified otherwise, always assume that a `status` of `0` indicates a
// success, showing that nothing went wrong.
union response {
	struct {
		int status;
	} gfx_draw_tex;
};

#endif
