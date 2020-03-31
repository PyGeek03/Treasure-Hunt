#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "BoardRow.h"

class Board
{
public:
    // Constructor
    Board();
    Board(short maxGuesses, short codeLength);

    // Destructor
    ~Board();

    // Accessor functions
    const std::vector<BoardRow>& getAllRows() const;
    size_t getGuessLen() const;
    short getCurrentRows() const;
    short getMaxRows() const;
    short getUnusedGuesses() const;


    // Mutator functions
    void addRow(BoardRow newRow);
    void emptyBoard();

private:
    bool isValidRow(BoardRow row);

    std::vector<BoardRow> allRows;
    size_t guessLen;  // the number of characters in a guess
    short currentRows;
    short maxRows;
};

#endif
