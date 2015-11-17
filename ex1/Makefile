CC=g++
CFLAGS=-I.
DEPS = Board.h Cell.h
FILES = Board.cpp Cell.cpp
OBJ = Board.o Cell.o
TESTOBJ = TestBoard.o 

$%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

board: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(OBJ) $(TESTOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

zip:
	zip ai_ex1 $(DEPS) $(FILES) Makefile 

.PHONY: clean

clean:
	rm -f *.o *~ core board
