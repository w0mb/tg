CC := gcc
CFLAGS := -Wall -Wextra

SRC_DIR := ../src
OBJ_DIR := ../obj
BIN_DIR := ../bin

APP := $(BIN_DIR)/app

SRCL := $(wildcard $(SRC_DIR)/*.c)
OBJL := $(patsubst $(SRC_DIR)/%c, $(OBJ_DIR)/%.o, $(SRCL))

all: dir $(APP)

dir: 
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	
$(OBJ_DIR)/%.o: $(SRCL)
	$(CC) $(CFLAGS) -c $< -o $@

$(APP): $(OBJL)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean