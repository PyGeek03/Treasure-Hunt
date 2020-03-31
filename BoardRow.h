#ifndef BOARDROW_H
#define BOARDROW_H

#include <string>
#include "Feedback.h"

class BoardRow
{
public:
    BoardRow();
    BoardRow(std::string newGuess, Feedback newFeedback);
    ~BoardRow();

    std::string getGuess() const;
    Feedback getFeedback() const;

private:
    std::string guess;
    Feedback feedback;
};

#endif // !BOARDROW_H
