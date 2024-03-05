SRC_DIR := src
OBJ_DIR := obj
TESTS_DIR := tests
EXE := encrypt

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ := $(filter-out $(OBJ_DIR)/$(EXE).o, $(OBJ))

TESTS_SRC := $(wildcard $(TESTS_DIR)/*.c)
TESTS := $(TESTS_SRC:$(TESTS_DIR)/%.c=$(TESTS_DIR)/%)

CFLAGS := -Wall -Wpedantic -Werror
CPPFLAGS := -Iinclude -MMD -MP

.PHONY: all clean tests run_tests

all: $(EXE)

$(EXE): $(OBJ) $(OBJ_DIR)/$(EXE).o
	$(CC) $^ -O2 -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(TESTS_DIR)/%.o: $(TESTS_DIR)/%.c
	$(CC) -g $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TESTS_DIR)/%: $(OBJ) $(TESTS_DIR)/%.o
	$(CC) $(filter-out $(OBJ_DIR)/$(EXE).o, $^) -o $@

tests: $(TESTS)

run_tests: $(TESTS)
	@for file in $^ ; do \
		echo "$${file}:" ; \
		./$${file} ; \
	done

clean:
	@$(RM) -rv $(OBJ_DIR)
	@$(RM) -v $(TESTS_DIR)/*.d $(TESTS_DIR)/*.o $(TESTS)

-include $(OBJ:.o=.d)
-include $(TESTS_SRC:.c=.d)
