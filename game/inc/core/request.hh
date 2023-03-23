#ifndef REQUEST_HH__
#define REQUEST_HH__

#include "core/graphics.hh"

enum class request_type {
	gfx_present,
	gfx_clear,
	gfx_draw_tex,
};

struct request {
	request_type type;
	
	union {
		struct {
			uint8_t r, g, b;
		} gfx_clear;

		struct {
			int x, y, w, h;
			texture tex_id;
		} gfx_draw_tex;
	};
};

struct response {
	request_type type;

	union {
		// tirimid: none of the requests currently give any meaningful response.
		// when adding responsive requests, define the responses here.
	};
};

#endif
