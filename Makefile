# Variables
BUILD_DIR = build
BINARY = ./$(BUILD_DIR)/renderer

# Default target
all: build

# Build logic
build:
	@echo "--- Building Renderer ---"
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && make

# Build and Run
run: build
	@echo "--- Running Renderer ---"
	@$(BINARY)

# Clean
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Build directory removed."

.PHONY: all build run clean