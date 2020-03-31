#include "Board.h"

Board::Board()
{
    maxRows = 0;
    guessLen = 0;
    emptyBoard();
}

Board::Board(short maxGuesses, short codeLength)
{
    maxRows = maxGuesses;
    guessLen = codeLength;
    emptyBoard();
}

// Destructor
Board::~Board() {}


// ACCESSOR FUNCTIONS

const std::vector<BoardRow>& Board::getAllRows() const { return allRows; }

// Returns the length of a guess
size_t Board::getGuessLen() const { return guessLen; }

// Returns the current number of rows in the board
short Board::getCurrentRows() const { return currentRows; }

// Returns maximum number of rows
short Board::getMaxRows() const { return maxRows; }

// Returns number of unused guesses (empty rows)
short Board::getUnusedGuesses() const
{
    return maxRows - currentRows;
}


// MUTATOR FUNCTIONS

void Board::addRow(BoardRow newRow)
{
    if (currentRows < maxRows and isValidRow(newRow)) {
        allRows.push_back(newRow);
        currentRows++;
    }
}

// Empties the board for a new round
void Board::emptyBoard()
{
    allRows.clear();
    currentRows = 0;
}

// PRIVATE FUNCTIONS

// check if row is valid for current board setup
bool Board::isValidRow(BoardRow row)
{
    std::string guess = row.getGuess();
    Feedback feedback = row.getFeedback();
    return (guess.length() == guessLen) and (feedback.getRightSlots() + feedback.getWrongSlots() <= guessLen);
}
