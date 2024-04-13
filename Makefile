CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra

SRC_DIR := source/cpp
OBJ_DIR := obj
BIN_DIR := bin

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

TARGET := $(BIN_DIR)/scheduler

all: $(TARGET)

$(TARGET): $(OBJ_DIR) $(BIN_DIR) $(OBJECTS) main.cpp
	$(CXX) $(CXXFLAGS) main.cpp $(OBJECTS) -o $(TARGET)
	cp -f entrada.txt $(BIN_DIR)/entrada.txt

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: clean all input
	./$(TARGET)

input:
	cp -f entrada.txt $(BIN_DIR)/entrada.txt

.PHONY: all clean