CC = gcc
CFLAGS = -fdiagnostics-color=always -I. -g -Wall
TARGET = bin/prog
SOURCES = $(wildcard *.c) $(wildcard */*.c) $(wildcard */*/*.c)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) | bin
	$(CC) $(CFLAGS) $(SOURCES) -o $@

bin:
	mkdir -p bin

clean:
	rm -f $(TARGET)
	rm -rf bin

rebuild: clean all 