CC = cc
CFLAGS = -I../raylib -I../src/libs
LDFLAGS = -L../raylib -L../src/libs -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = ../bin/a.out
OBJ_DIR = ../obj
SRC_DIR = ../src
LIBS_DIR = $(SRC_DIR)/libs
GAMELOGIC_DIR = $(SRC_DIR)/gameLogic
MAIN_DIR = $(SRC_DIR)/main

SRCS_GAMELOGIC = $(wildcard $(GAMELOGIC_DIR)/*.c)
SRCS_MAIN = $(wildcard $(MAIN_DIR)/*.c)
OBJS_GAMELOGIC = $(patsubst $(GAMELOGIC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_GAMELOGIC))
OBJS_MAIN = $(patsubst $(MAIN_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_MAIN))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS_GAMELOGIC) $(OBJS_MAIN)
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(GAMELOGIC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(MAIN_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
