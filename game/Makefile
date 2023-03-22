include config.mk

CPP_REAL_SOURCES := $(patsubst %, $(SRC_DIR)/%, $(CPP_SOURCES))
CPP_OBJECTS := $(patsubst $(SRC_DIR)/%.cc, $(LIB_DIR)/%.o, $(CPP_REAL_SOURCES))
C_REAL_SOURCES := $(patsubst %, $(SRC_DIR)/%, $(C_SOURCES))
C_OBJECTS := $(patsubst $(SRC_DIR)/%.c, $(LIB_DIR)/%.o, $(C_REAL_SOURCES))

clean:
	$(RM_RF) $(OUT_BIN_LINUX) $(OUT_BIN_WINDOWS) $(LIB_DIR)/*

linux: $(CPP_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS_LINUX) -o $(OUT_BIN_LINUX) $^

windows: $(CPP_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS_WINDOWS) -o $(OUT_BIN_WINDOWS) $^

$(LIB_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $@
	$(RMDIR) $@
	$(CC) $(CFLAGS) -o $@ $<

$(LIB_DIR)/%.o: $(SRC_DIR)/%.cc
	$(MKDIR_P) $@
	$(RMDIR) $@
	$(CPP) $(CPPFLAGS) -o $@ $<
