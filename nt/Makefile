CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Wpedantic -Werror -g -fPIC
LDFLAGS=
AR=ar
ARFLAGS=rcs

INCLUDE_DIR=include
SRC_DIR=src
OBJ_DIR=obj
LIB_DIR=lib
TEST_DIR=tests

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(LIB_DIR)/libntob.a

$(LIB_DIR)/libntob.a: $(OBJS)
	@mkdir -p $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR)

# Simple test build (no sanitizers yet)
$(TEST_DIR)/test_main: $(OBJS) $(TEST_DIR)/test_main.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) $^ -pthread -o $@

test: $(TEST_DIR)/test_main
	@./$<

# Sanitizer builds
asan: CFLAGS += -fsanitize=address,undefined
asan: LDFLAGS += -fsanitize=address,undefined
asan: clean all $(TEST_DIR)/test_main
	@./$(TEST_DIR)/test_main

ubsan: CFLAGS += -fsanitize=undefined
ubsan: LDFLAGS += -fsanitize=undefined
ubsan: clean all $(TEST_DIR)/test_main
	@./$(TEST_DIR)/test_main

.PHONY: all clean test asan ubsan
