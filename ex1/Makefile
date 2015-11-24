CC = g++
INC = -I.
CFLAGS = -Wall -g $(INC)

FILES = Definitions.cpp Path.cpp Cell.cpp Board.cpp
MAIN = AIEx1.cpp
OBJ = $(FILES:.cpp=.o)
TARGET = a.out

all: $(OBJ)
	$(CC) -o $(TARGET) $^ $(MAIN) $(CFLAGS)

$%.o: %.cpp %.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) $(OBJ) $(TARGET) *~ core 

zip: clean
	zip ai_ex1 $(FILES) $(FILES:.cpp=.h) $(MAIN) Makefile details.txt
