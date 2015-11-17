CC=g++
CFLAGS=-I.
DEPS = Board.h Cell.h Service.h
FILES = Board.cpp Cell.cpp Service.cpp
OBJ = Board.o Cell.o Service.o
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
