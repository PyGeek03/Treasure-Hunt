#include "Genie.h"

Genie::Genie() : Player()
{
    // load the comments from files
    loadComments(goodComments, "good.txt");
    loadComments(averageComments, "average.txt");
    loadComments(badComments, "bad.txt");
}

// Destructor
Genie::~Genie() {}

// ACCESSOR FUNCTIONS

// Returns the std::string "Genie"
std::string Genie::getName() const
{
    return "Genie";
}

// Returns a random comment based on player's performance
std::string Genie::getComment(Performance playerPerformance) const
{
    std::vector<std::string>& commentVector = *commentTypes[playerPerformance];
    size_t randomIndex = rand() % commentVector.size();
    std::string randomComment = commentVector[randomIndex];
    return randomComment;
}

// Returns a secret code
std::string Genie::newCode(short codeLength, short codeRange)
{
    // declare and initialize local variables
    std::string newCode = "";
    short newDigit = 0;
    short duplicateChance = 0;
    char duplicatedDigit = '0';

    // add digits to newCode
    for (short i = 0; i != codeLength; i++)
    {
        // first, decide whether to duplicate a previous digit
        duplicateChance = rand() % 10;

        if (duplicateChance == 0 && i != 0) {
            // if duplicateChance == 1 and newCode is not empty (i == newCode.length()),
            // choose a previous digit in newCode to duplicate
            duplicatedDigit = newCode[rand() % i];
            newCode += duplicatedDigit;
        }
        else
        {
            // if not, generate a random digit and add to newCode
            newDigit = rand() % codeRange + 1;
            newCode += std::to_string(newDigit);
        }
    }

    return newCode;
}

// PRIVATE FUNCTIONS

// Load the comments from files into the vectors; helper function for constructor
void Genie::loadComments(std::vector<std::string>& commentsVector, std::string commentsFile)
{
    std::ifstream fileToRead(commentsFile);
    if (fileToRead.is_open()) {
        // read the file and add each line to goodComments
        std::string line = "";
        while (!fileToRead.eof()) {
            getline(fileToRead, line);
            commentsVector.push_back(line);
        }
    }
    fileToRead.close();
}
