# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -c

# Directories
SRC_DIR = src
BUILD_DIR = build

# Library Name
LIB_NAME = SML.a

# Object Files (located in src/)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))

$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

# Compile Source Files into Object Files in build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Clean
.PHONY: clean
clean:
	rm -f $(LIB_NAME) $(BUILD_DIR)/*.o
	rmdir $(BUILD_DIR) 2>/dev/null || true
