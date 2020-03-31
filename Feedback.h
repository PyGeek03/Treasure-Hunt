#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>

class Feedback
{
public:
    Feedback();
    Feedback(std::size_t right, std::size_t wrong);

    std::size_t getRightSlots() const;
    std::size_t getWrongSlots() const;

private:
    std::size_t rightSlots;
    std::size_t wrongSlots;
};

#endif // !FEEDBACK_H
