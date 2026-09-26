CXX := g++

TARGET := duel

SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include

SRC := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

CXXFLAGS := -Wall -Wextra -std=c++17 -I$(INCLUDE_DIR)
CXXFLAGS += $(shell pkg-config --cflags raylib)

LDFLAGS := $(shell pkg-config --libs raylib)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
