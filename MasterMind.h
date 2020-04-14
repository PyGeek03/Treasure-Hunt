#ifndef MASTERMIND_H
#define MASTERMIND_H

#include "Board.h"
#include "HumanPlayer.h"
#include "Genie.h"

class MasterMind
{
public:
    // Default constructor
    MasterMind();

    // Default destructor
    ~MasterMind();

    // Accessor functions
    const HumanPlayer& getPlayer() const;
    const Board& getBoard() const;
    const Genie& getGenie() const;
    
    std::string getCode() const;
    std::string getIntroFile() const;
    std::string getPlayerLevel() const;
    short getRoundsLeft() const;
    short getCurrentRound() const;
    short getCodeRange() const;
    size_t getCodeLength() const;
    std::string getGenieComment() const;
    bool roundNotEnd() const;
    bool gameNotEnd() const;
    std::string getWinnerName() const;
    short getWinnerEarning() const;


    // Mutator functions
    void newPlayer(std::string name, short level);
    void newRound();
    void newGuess(std::string guess);
    void resetGame();
    void quit();

private:
    void resetRound();
    bool roundHasEnded();
    void endRound();
    void endGame();
    Feedback computeFeedback(std::string guess);

    Board board;
    HumanPlayer player;
    Genie genie;
    Player* winner;

    std::string code;
    bool roundEnded;
    bool playerQuitted;
    size_t lastRightSlots;
    size_t consecutiveBadGuesses;
    size_t totalBadGuesses;
    size_t winnerEarning;

    // Game constants
    const std::string introFile = "MasterMindIntro.txt";
    static const short MAX_ROUNDS = 5;

    // Level 1: Apprentice
    // Level 2: Master
    // Level 3: Legend
    const std::string levels[4] = { "None", "Apprentice", "Master", "Legend" };

    // Level 1: 4 digits from 0 to 5, 10 guesses
    // Level 2: 5 digits from 0 to 7, 12 guesses
    // Level 3: 6 digits from 0 to 9, 14 guesses
    const short codeLength[4] = { 0, 4, 5, 6 };
    const short codeRange[4] = { 0, 5, 7, 9 };
    const short maxGuesses[4] = { 0, 10, 12, 14 };
};


#endif // !MASTERMIND_H
