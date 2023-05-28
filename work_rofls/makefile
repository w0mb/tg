RAYLIB_PATH := C:/raylib/raylib/src/
RAYLIB_LIBS := -L$(RAYLIB_PATH) -lraylib -lopengl32 -lgdi32 -lwinmm
CC := C:/raylib/w64devkit/bin/gcc.exe
CFLAGS := -Wall -Wextra

SRC_DIR := ../src
OBJ_DIR := ../obj
BIN_DIR := ../bin

APP := $(BIN_DIR)/app

SRCL := $(wildcard $(SRC_DIR)/*.c)
OBJL := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCL))

all: dir $(APP)

dir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(RAYLIB_PATH)

$(APP): $(OBJL)
	$(CC) $(CFLAGS) $^ -o $@ $(RAYLIB_LIBS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
