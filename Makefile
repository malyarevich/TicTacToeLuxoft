CC			= g++
CFLAGS		= -Wall
PROG_NAME   = TicTacToeLuxoft

SOURCE_DIR	= ./TicTacToeLuxoft
BIN_DIR		= ./bin
BUILD_DIR	= $(BIN_DIR)/build

SOURCE_LIST	= $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECT_LIST	= $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCE_LIST:.cpp=.o)))

.PHONY: all clean $(BIN_DIR)/$(PROG_NAME) compile build_dirs $(BUILD_DIR)/%.o


all: $(BIN_DIR)/$(PROG_NAME)

$(BIN_DIR)/$(PROG_NAME): compile
	$(CC) $(OBJECT_LIST) -o $@

compile: build_dirs $(OBJECT_LIST)

#make $(BIN_DIR) and $(BUILD_DIR) 
build_dirs:
	mkdir -p $(BUILD_DIR) 

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BIN_DIR)/$(PROG_NAME) $(BUILD_DIR)/*.o $(BUILD_DIR)/ $(BIN_DIR)/
