CC=g++
CFLAGS=-I.
DEPS = Board.h
OBJ = Board.o TestBoard.o 

$%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

board: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core 
