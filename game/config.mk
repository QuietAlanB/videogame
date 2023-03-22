SRC_DIR := src
INC_DIR := inc
LIB_DIR := lib

MKDIR_P := mkdir -p
RMDIR := rmdir
RM_RF := rm -rf

CC := gcc
CPP := g++
LD := g++

CFLAGS := -std=c17 -pedantic -c -I$(INC_DIR)
CPPFLAGS := -std=c++17 -pedantic -c -I$(INC_DIR)
LDFLAGS_LINUX := -lSDL2
LDFLAGS_WINDOWS :=

OUT_BIN_LINUX := game
OUT_BIN_WINDOWS := game.exe

CPP_SOURCES := main.cc app.cc
C_SOURCES :=
