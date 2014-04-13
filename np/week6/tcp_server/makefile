CC=gcc
CFLAGS=-I.
DEPS = serverh.h
OBJ = main.o serverTCP.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
