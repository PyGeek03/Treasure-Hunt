#ifndef IO_H
#define IO_H

#include <iostream>
#include <sstream>
#include <algorithm>
#include "MasterMind.h"

class IO
{
public:
    IO();
    ~IO();

    void newGame();

private:
    std::string feedbackHeader = "  Secret Code  ";

    // Game objects
    MasterMind game;
    const HumanPlayer& player = game.getPlayer();
    const Board& board = game.getBoard();
    const Genie& genie = game.getGenie();

    // Main game interface functions
    void gameLoop();
    void displayTitle(size_t screenWidth);
    void displayIntro();
    void displayRow(std::string formattedGuess, std::string formattedFeedback);
    void displayBoard();
    void displayRound();
    void displayGeniePrompt();
    void displayResults();
    void playerQuits();
    std::string askForGuess();

    // Helper functions
    size_t getGuessWidth();
    size_t getFeedbackWidth();
    size_t getBoardWidth();
    std::string formatGuess(std::string guess);
    std::string formatFeedback(Feedback feedback);
    std::string multiplyStr(size_t times, std::string s);
    void printCentred(std::string line, size_t viewWidth);
    bool validGuess(std::string guess);
    std::string removeWhiteSpace(std::string s);
    std::string trimWhiteSpace(std::string s);
    bool validDigits(std::string input);
    short charToShort(char c);

    std::string askForString(std::string question);
    int askForNumber(std::string question, int min, int max);
    char askForLetter(std::string question, std::string validOptions);
};

#endif // !IO_H
