include config.mk

CPP_REAL_SOURCES := $(patsubst %, $(SRC_DIR)\%, $(CPP_SOURCES))
CPP_OBJECTS := $(patsubst $(SRC_DIR)\%.cc, $(LIB_DIR)\%.o, $(CPP_REAL_SOURCES))
C_REAL_SOURCES := $(patsubst %, $(SRC_DIR)\%, $(C_SOURCES))
C_OBJECTS := $(patsubst $(SRC_DIR)\%.c, $(LIB_DIR)\%.o, $(C_REAL_SOURCES))

all: $(OUT_BIN_WINDOWS)

clean:
	rd /s /q $(OUT_BIN_WINDOWS) $(LIB_DIR)\*

$(OUT_BIN_WINDOWS): $(CPP_OBJECTS) $(C_OBJECTS)
	$(LD) $(LDFLAGS_WINDOWS) -o $(OUT_BIN_LINUX) $^

$(LIB_DIR)\%.o: $(SRC_DIR)\%.c
	mkdir $@
	rmdir $@
	$(CC) $(CFLAGS_WINDOWS) -o $@ $<

$(LIB_DIR)\%.o: $(SRC_DIR)\%.cc
	mkdir $@
	rmdir $@
	$(CPP) $(CPPFLAGS_WINDOWS) -o $@ $<
