CC = cc
CFLAGS = -I../raylib/src
LDFLAGS = -L../raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = ../bin/a.out
OBJ_DIR = ../obj
SRC_DIR = ../src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
