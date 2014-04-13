CC=gcc
CFLAGS=-I.
DEPS = serverh.h
OBJ = main.o server1.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
