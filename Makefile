CC=clang
CFLAGS=-I.

OBJ=$(patsubst src/%.c, bin/%.o, $(wildcard src/*.c))

bin/%.o: src/%.c
	$(CC) -c -g -o $@ $< $(CFLAGS)

clean:
	rm -rf bin && mkdir -p bin

all: $(OBJ)
	$(CC) -o bin/uvm $(OBJ)

.DEFAULT: all
