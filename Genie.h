#ifndef GENIE_H
#define GENIE_H

#include <vector>
#include <fstream>
#include "Player.h"
#include "Enums.h"

class Genie : public Player
{
public:
    // Constructor
    Genie();

    // Destructor
    ~Genie();

    // Accessor functions
    std::string getName() const;
    std::string getComment(Performance playerPerformance) const;
    std::string newCode(short codeLength, short codeRange);

private:
    std::vector<std::string> goodComments;
    std::vector<std::string> averageComments;
    std::vector<std::string> badComments;
    std::vector<std::string>* commentTypes[3] = { &goodComments, &averageComments, &badComments };

    void loadComments(std::vector<std::string>& commentsVector, std::string commentsFile);
};

#endif // !GENIE_H
