CC=gcc
SRC=game.c
CCFLAGS=-Wall -Wextra -Werror -std=c11
BUILD=./game

all: test
rebuild: clean all

game:
	$(CC) -DENG $(CCFLAGS) $(SRC) -o $(BUILD)

game_debug:
	$(CC) $(CCFLAGS) -g $(SRC) -o $(BUILD)

test: clean game
	./$(BUILD)

clangi:
	find -iname '*.h' -o -iname '*.c' | xargs clang-format -i --style=Google
clangn:
	find -iname '*.h' -o -iname '*.c' | xargs clang-format -n --style=Google
cppcheck: rebuild
	find -iname '*.c' | xargs cppcheck --enable=all --suppress=missingIncludeSystem

valgrind: clean game_debug
	valgrind --tool=memcheck --track-origins=yes --leak-check=yes -s $(BUILD)

clean:
	rm -rf *.o *.a *.out $(BUILD)
