# Makefile for the search program

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = search

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	rm -f $(TARGET)

.PHONY: all clean
