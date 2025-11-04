EXEC ?= main
OBJ_DIR := ./io/objects
EXEC_DIR := ./io

MAIN_SRC := $(if $(filter main,$(EXEC)),./src/main.cc,./test/$(EXEC).cc)
MAIN_OBJ := $(OBJ_DIR)/$(EXEC).o

SUPPORT_SRC := $(filter-out ./src/main.cc, $(wildcard ./src/*.cc))
SUPPORT_OBJ := $(patsubst ./src/%.cc,$(OBJ_DIR)/%.o,$(SUPPORT_SRC))

BIN := $(EXEC_DIR)/$(EXEC).out

all: $(BIN)

makedirectories:
	mkdir -p $(EXEC_DIR)
	mkdir -p $(OBJ_DIR)

$(BIN): $(SUPPORT_OBJ) $(MAIN_OBJ)
	g++ -O2 $^ -o $@

$(OBJ_DIR)/%.o: ./src/%.cc makedirectories
	g++ -c -O2 $< -o $@

$(MAIN_OBJ): $(MAIN_SRC) makedirectories
	g++ -c -O2 $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o

play:
	./io/main.out ./io/newGalaxy.txt ./io/savedGalaxy.txt 2>error.log

.SECONDARY: $(SUPPORT_OBJ) $(MAIN_OBJ) makedirectories
.PHONY: clean play
