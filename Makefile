CFLAGS=-I.

OBJ=$(patsubst %.c, bin/%.o, $(wildcard *.c))

bin/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf bin && mkdir -p bin

all: $(OBJ)
	$(CC) -o bin/uvm bin/*.o

.PHONY: all
