CC = g++
INC = -I.
CFLAGS = -Wall -g $(INC)
FILES = Board.cpp Cell.cpp Service.cpp
OBJ = $(FILES:.cpp=.o)
EXECUTABLE = a.out
TESTOBJ = TestBoard.o
TESTTARGET = test


all: $(OBJ)
	$(CC) -o $(EXECUTABLE) $^ $(CFLAGS)

$%.o: %.cpp %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(TESTTARGET): $(OBJ) $(TESTOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJ) $(TESTOBJ) $(EXECUTABLE) $(TESTTARGET) *~ core 

zip: clean
	zip ai_ex1 $(FILES) $(FILES:.cpp=.h) Makefile details.txt
