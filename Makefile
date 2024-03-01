SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .
EXE := $(BIN_DIR)/encrypt

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CFLAGS := -Wall -Wpedantic
CPPFLAGS := -Iinclude -MMD -MP

.PHONY: all clean

all: $(EXE)

$(BIN_DIR):
	mkdir -p $@

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $^ -O2 -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)

DES_tests: tests/DES_tests.c DES.h DES.c
	gcc -g $(CFLAGS) -o tests/DES tests/DES_tests.c

polyalg_tests: tests/polyalg_tests.c polyalg.h polyalg.c
	gcc -g $(CFLAGS) -o tests/polyalg tests/polyalg_tests.c

tests: DES_tests polyalg_tests
