# Directories
BUILD_DIR = obj
SRC_DIR = src
LIB_DIR = lib

# Compiler
CXX = clang++

# Flags: Compile, more warnings, use C++20, enable debugging symbols and include path
CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++20 -g -fstandalone-debug -I$(LIB_DIR)
LNFLAGS = -lncurses

# Binaries
TARGET = binary
TESTS = tests

# Source
CPP_SOURCE = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/test.cpp, $(wildcard $(SRC_DIR)/*))
 
# Headers
HPP_SOURCE = $(wildcard $(LIB_DIR)/*)
 
# Objects
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(BUILD_DIR),$(CPP_SOURCE)))
 
# Compilation and linking
all: obj $(TARGET)

$(TARGET): $(OBJ) ./$(BUILD_DIR)/main.o
	$(CXX) $^ -o $@ $(LNFLAGS)
 
./$(BUILD_DIR)/main.o: ./$(SRC_DIR)/main.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@

test: obj $(TESTS)

$(TESTS): $(OBJ) $(BUILD_DIR)/test.o
	$(CXX) $^ -lgtest -o $@ $(LNFLAGS)
	./$(TESTS)

./$(BUILD_DIR)/test.o: ./$(SRC_DIR)/test.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@

./$(BUILD_DIR)/%.o: ./$(SRC_DIR)/%.cpp ./$(LIB_DIR)/%.hpp
	$(CXX) $< $(CXXFLAGS) -o $@
 
obj:
	@ test -d $(BUILD_DIR) && true || mkdir -p $(BUILD_DIR)
 
clean:
	@ rm -rf $(BUILD_DIR) $(TARGET) $(TESTS) *~
 
.PHONY: all clean obj test
