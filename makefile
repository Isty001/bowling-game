TEST_SOURCES = $(shell find tests src -name '*.c' )
GCC_FLAGS = -Wall -std=c11 

test:
	gcc $(TEST_SOURCES) $(GCC_FLAGS) -g -o game.o && ./game.o