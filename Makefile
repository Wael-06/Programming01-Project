# Project name
TARGET := bank_system

# Compiler
CC := gcc

# Directories
SRC_DIR := src
OBJ_DIR := build

# Flags
CFLAGS := -Wall -Wextra -std=c11 -I$(SRC_DIR) -MMD -MP
LDFLAGS :=

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# Include dependencies
-include $(DEPS)

.PHONY: all clean
