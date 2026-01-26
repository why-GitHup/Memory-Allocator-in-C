# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -g -D_DEFAULT_SOURCE -fPIC
LDFLAGS = -shared

# Directories
SRC_DIR = src
BIN_DIR = bin
LIB_DIR = lib

# Source files
SRCS = $(SRC_DIR)/avl.c $(SRC_DIR)/LL.c $(SRC_DIR)/memAllo.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(LIB_DIR)/%.o,$(SRCS))

# Shared library
SHARED_LIB = $(LIB_DIR)/libmemallo.so

# Target executable
TARGET = $(BIN_DIR)/memAllo

# Default target
all: $(SHARED_LIB) $(TARGET)

# Create directories if they don't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIB_DIR):
	mkdir -p $(LIB_DIR)

# Build shared library
$(SHARED_LIB): $(LIB_DIR)/avl.o $(LIB_DIR)/LL.o $(LIB_DIR)/memAllo.o | $(LIB_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Link object files to create executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS:-fPIC=) $(OBJS) -o $(TARGET)

# Compile source files to object files in lib directory
$(LIB_DIR)/%.o: $(SRC_DIR)/%.c | $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Dependencies
$(LIB_DIR)/avl.o: $(SRC_DIR)/avl.c $(SRC_DIR)/avl.h
$(LIB_DIR)/LL.o: $(SRC_DIR)/LL.c $(SRC_DIR)/LL.h $(SRC_DIR)/memAllo.h
$(LIB_DIR)/memAllo.o: $(SRC_DIR)/memAllo.c $(SRC_DIR)/memAllo.h $(SRC_DIR)/avl.h

# Clean build artifacts
clean:
	rm -f $(LIB_DIR)/*.o $(SHARED_LIB) $(TARGET)

# Clean and rebuild
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install shared library (optional)
install: $(SHARED_LIB)
	cp $(SHARED_LIB) /usr/local/lib/
	ldconfig

# Phony targets
.PHONY: all clean rebuild run install

