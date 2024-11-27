SRC_DIR = src
INCLUDE_DIR = include
INCLUDE_DIR2 = include/tesselix
LIB_DIR = lib
BIN_DIR = bin

# Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SOURCES))
EXECUTABLE = $(BIN_DIR)/main

# Compiler and Flags
CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -I$(INCLUDE_DIR2) -Wall -Werror
LDFLAGS = -L$(LIB_DIR) -ltesselix

# Targets
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*.o $(EXECUTABLE)