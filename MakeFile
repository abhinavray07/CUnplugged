# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = CUnplugged

# Source files
SRCS = src/main.c src/cli.c src/library.c src/song.c src/playlist.c src/load.c

# Object files
OBJS = main.o cli.o library.o song.o playlist.o load.o

# Default target
all: $(TARGET)

# Link object files
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	@echo Build complete! Run: ./$(TARGET)

# Compile each source file
main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

cli.o: src/cli.c
	$(CC) $(CFLAGS) -c src/cli.c

library.o: src/library.c
	$(CC) $(CFLAGS) -c src/library.c

song.o: src/song.c
	$(CC) $(CFLAGS) -c src/song.c

playlist.o: src/playlist.c
	$(CC) $(CFLAGS) -c src/playlist.c

load.o: src/load.c
	$(CC) $(CFLAGS) -c src/load.c

# Clean
clean:
	del /Q *.o $(TARGET).exe 2>nul || rm -f *.o $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run