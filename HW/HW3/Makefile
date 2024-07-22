CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = search
SRCS = search.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
