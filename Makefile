CC ?= cc
CFLAGS ?= -std=c17 -O2 -Wall -Wextra -Wpedantic -Werror -Iinclude
LDLIBS = -lsqlite3 -lcrypto
OBJ = build/engine.o build/main.o
all: ctfbot
build:
	mkdir -p build
build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@
ctfbot: $(OBJ)
	$(CC) $(OBJ) $(LDLIBS) -o $@
test: build/engine.o tests/test_engine.c
	$(CC) $(CFLAGS) tests/test_engine.c build/engine.o $(LDLIBS) -o build/test_engine
	./build/test_engine
check: clean all test
	CTFBOT_DB=/tmp/ctfbot-check.db ./ctfbot init
	rm -f /tmp/ctfbot-check.db /tmp/ctfbot-check.db-shm /tmp/ctfbot-check.db-wal
clean:
	rm -rf build ctfbot
.PHONY: all test check clean
