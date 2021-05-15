all:
	make clean
	make build/main

build/main: build/main.o
	$(CC) -o $@ $^

build/main.o: src/main.c
	$(COMPILE.c) -o $@ $^

clean:
	$(RM) build/*

.PHONY: all clean
