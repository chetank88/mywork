CC=gcc
CFLAGS=-I.
DEPS = fragment.h
OBJ = main.o fragment.o defragment.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
