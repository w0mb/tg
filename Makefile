CC = cc
CFLAGS = -I/raylib/src
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = a.out
SRCS = main.c

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
