CC = g++
INC = -I.
CFLAGS = -Wall -g $(INC)

FILES = Plain.cpp Cluster.cpp
MAIN = AIEx3.cpp
OBJ = $(FILES:.cpp=.o)
TARGET = a.out

all: $(OBJ)
	$(CC) -o $(TARGET) $^ $(MAIN) $(CFLAGS)

$%.o: %.cpp %.h
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(RM) $(OBJ) $(TARGET) *~ core 

zip: clean
	zip ai_ex3 $(FILES) $(FILES:.cpp=.h) $(MAIN) Makefile details.txt
