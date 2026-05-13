# Makefile for Student Grade Calculator
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = -lstdc++fs

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Source and object files
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/Course.cpp \
          $(SRC_DIR)/Student.cpp \
          $(SRC_DIR)/GradeCalculator.cpp \
          $(SRC_DIR)/ReportGenerator.cpp \
          $(SRC_DIR)/GradeObserver.cpp \
          $(SRC_DIR)/FileManager.cpp

OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/StudentGradeCalculator

# Default target
all: $(TARGET)

# Create target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "✓ Build completed successfully!"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo "Compiling: $<"

# Run the program
run: $(TARGET)
	$(TARGET)

# Clean build artifacts
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "✓ Cleaned build artifacts"

# Help target
help:
	@echo "Available targets:"
	@echo "  make all    - Build the project"
	@echo "  make run    - Build and run the project"
	@echo "  make clean  - Remove build artifacts"
	@echo "  make help   - Display this help message"

.PHONY: all run clean help
