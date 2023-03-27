include ../windows_deps.mk

SRC_DIR := src
INC_DIR := inc
LIB_DIR := lib

CC := gcc
CPP := g++
LD := g++

C_MODS :=
CPP_MODS := -DFAST_INVERSE_SQRT

CFLAGS_LINUX := -std=c17 -pedantic -c -I$(INC_DIR) $(C_MODS)
CPPFLAGS_LINUX := -std=c++20 -pedantic -c -I$(INC_DIR) $(CPP_MODS)
LDFLAGS_LINUX := -lSDL2

CFLAGS_WINDOWS := \
	-std=c17 \
	-pedantic \
	-c \
	-I$(INC_DIR) \
	-I..\\$(DEPS_WINDOWS_SDL2_INC_DIR)

CPPFLAGS_WINDOWS := \
	-std=c++20 \
	-pedantic \
	-c \
	-I$(INC_DIR) \
	-I..\\$(DEPS_WINDOWS_SDL2_INC_DIR)

LDFLAGS_WINDOWS := \
	-L..\\$(DEPS_WINDOWS_SDL2_LIB_DIR) \
	-lmingw32 \
	-lSDL2main \
	-lSDL2

OUT_BIN_LINUX := game
OUT_BIN_WINDOWS := game.exe

# when adding sources, use `/` path separators.
# the `C(PP)_SOURCES_WINDOWS` will automatically be given `\\` paths
CPP_SOURCES := \
	main.cc \
	core/app.cc \
	core/graphics.cc \
	core/keyboard.cc \
	core/world.cc \
	core/timer.cc \
	core/audio.cc \
	core/iface/graphics_iface.cc \
	core/iface/keyboard_iface.cc \
	core/iface/world_iface.cc \
	core/iface/timer_iface.cc \
	core/comp/transform_comp.cc \
	core/comp/sprite_comp.cc \
	core/comp/aaboxcol_comp.cc \
	core/comp/dynamic_comp.cc \
	core/comp/colbase.cc \
	util/log.cc \
	util/vec2.cc \
	util/mat2.cc

CPP_SOURCES_LINUX := $(CPP_SOURCES)
CPP_SOURCES_WINDOWS := $(subst /,\\,$(CPP_SOURCES))

C_SOURCES :=
C_SOURCES_LINUX := $(C_SOURCES)
C_SOURCES_WINDOWS := $(subst /,\\,$(C_SOURCES))
