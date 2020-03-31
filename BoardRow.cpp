#include "BoardRow.h"

BoardRow::BoardRow()
{
    guess = "";
    feedback = Feedback();
}

BoardRow::BoardRow(std::string newGuess, Feedback newFeedback)
{
    guess = newGuess;
    feedback = newFeedback;
}

BoardRow::~BoardRow() {}

std::string BoardRow::getGuess() const { return guess; }

Feedback BoardRow::getFeedback() const { return feedback; }
