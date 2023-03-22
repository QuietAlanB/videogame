include ../windows_deps.mk

SRC_DIR := src
INC_DIR := inc
LIB_DIR := lib

CC := gcc
CPP := g++
LD := g++

CFLAGS_LINUX := -std=c17 -pedantic -c -I$(INC_DIR)
CPPFLAGS_LINUX := -std=c++17 -pedantic -c -I$(INC_DIR)

CFLAGS_WINDOWS := \
	-std=c17 \
	-pedantic \
	-c \
	-I$(INC_DIR) \
	-I$(DEPS_WINDOWS_SDL2_INC_DIR)

CPPFLAGS_WINDOWS := \
	-std=c++17 \
	-pedantic \
	-c \
	-I$(INC_DIR) \
	-I$(DEPS_WINDOWS_SDL2_INC_DIR)

LDFLAGS_LINUX := -lSDL2
LDFLAGS_WINDOWS := -L..\\$(DEPS_WINDOWS_SDL2_LIB_DIR) -lSDL2

OUT_BIN_LINUX := game
OUT_BIN_WINDOWS := game.exe

CPP_SOURCES := main.cc app.cc
C_SOURCES :=
