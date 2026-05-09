# 1. Detect if we are on Windows or not to handle the binary extension
ifeq ($(OS),Windows_NT)
    EXT = .exe

    GENERATOR = -G "MinGW Makefiles"
else
    EXT =

    GENERATOR = 
endif

BUILD_DIR = build
BINARY = $(BUILD_DIR)/renderer$(EXT)

# Use 'all' as the default target
all: build

# 'cmake -E make_directory' works on Windows, Mac, and Linux without error
build:
#  	@echo --- Building Project ---
	@cmake -E make_directory $(BUILD_DIR)
	@cmake -B $(BUILD_DIR) -S . $(GENERATOR)
	@cmake --build $(BUILD_DIR)

# Run the binary using a relative path that works across shells
run: 
# 	@echo --- Running Project ---
	@$(BINARY)

# 'cmake -E rm -rf' is the universal 'delete folder' command
clean:
#  	@echo --- Cleaning Up ---
	@cmake -E rm -rf $(BUILD_DIR)

.PHONY: all build run clean