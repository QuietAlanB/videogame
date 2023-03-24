include config.mk

CPP_REAL_SOURCES := $(patsubst %, $(SRC_DIR)/%, $(CPP_SOURCES_LINUX))
CPP_OBJECTS := $(patsubst $(SRC_DIR)/%.cc, $(LIB_DIR)/%.o, $(CPP_REAL_SOURCES))
C_REAL_SOURCES := $(patsubst %, $(SRC_DIR)/%, $(C_SOURCES_LINUX))
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(LIB_DIR)/%.o, $(C_REAL_SOURCES))

all: $(OUT_BIN_LINUX)

clean:
	rm -rf $(OUT_BIN_LINUX) $(LIB_DIR)/*

$(OUT_BIN_LINUX): $(CPP_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS_LINUX) -o $@ $^

$(LIB_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p $@
	@ rmdir $@
	$(CC) $(CFLAGS_LINUX) -o $@ $<

$(LIB_DIR)/%.o: $(SRC_DIR)/%.cc
	@ mkdir -p $@
	@ rmdir $@
	$(CPP) $(CPPFLAGS_LINUX) -o $@ $<
