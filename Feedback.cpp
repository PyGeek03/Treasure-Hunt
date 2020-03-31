#include "Feedback.h"

Feedback::Feedback()
{
    rightSlots = 0;
    wrongSlots = 0;
}

Feedback::Feedback(std::size_t right, std::size_t wrong)
{
    rightSlots = right;
    wrongSlots = wrong;
}

std::size_t Feedback::getRightSlots() const { return rightSlots; }

std::size_t Feedback::getWrongSlots() const { return wrongSlots; }
