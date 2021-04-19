target := bin/simulator
SRC_DIR := src
OBJ_DIR := obj
HEADER_DIR := include
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

$(target): $(OBJ_FILES)
	g++ $^ -o $@
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADER_DIR)/%.h
	g++ -c $< -o $@

clean :
	-rm $(target) $(OBJ_FILES)