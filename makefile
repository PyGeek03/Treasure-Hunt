CXX = g++
CXXFLAGS = -Wall
OBJ = main.o IO.o MasterMind.o Feedback.o Genie.o HumanPlayer.o Player.o Board.o BoardRow.o

all: main

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)

main.o: IO.h

IO.o: IO.h

MasterMind.o: MasterMind.h

Feedback.o: Feedback.h

Genie.o: Genie.h

HumanPlayer.o: HumanPlayer.h

Player.o: Player.h

Board.o: Board.h

BoardRow.o: BoardRow.h

.PHONY: clean

clean :
	rm *.o
