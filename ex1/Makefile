CC = g++
INC = -I.
CFLAGS = -Wall -g $(INC)

FILES = Definitions.cpp Path.cpp Cell.cpp Board.cpp Service.cpp
OBJ = $(FILES:.cpp=.o)
TARGET = a.out

TESTOBJ = TestBoard.o
TESTTARGET = test


all: $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS)

$%.o: %.cpp %.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(TESTTARGET): $(OBJ) $(TESTOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJ) $(TESTOBJ) $(TARGET) $(TESTTARGET) *~ core 

zip: clean
	zip ai_ex1 $(FILES) $(FILES:.cpp=.h) Makefile details.txt
