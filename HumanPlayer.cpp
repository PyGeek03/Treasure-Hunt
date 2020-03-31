#include "HumanPlayer.h"

// Default constructor
HumanPlayer::HumanPlayer() : Player()
{
	skillLevel = 0;
	roundsPlayed = 0;
}

// Usual creation constructor
HumanPlayer::HumanPlayer(std::string name, short level) : Player(name)
{
	skillLevel = level;
	roundsPlayed = 0;
}

// Destructor
HumanPlayer::~HumanPlayer() {}


// ACCESSOR FUNCTIONS

// Returns the player's name
std::string HumanPlayer::getName() const { return name; }

// Returns the player's skill level, as a number
short HumanPlayer::getLevel() const { return skillLevel; }

// Returns the current number of rounds played
short HumanPlayer::getRoundsPlayed() const { return roundsPlayed; }


// MUTATOR FUNCTIONS

// Resets human player's stats (except for skillLevel)
void HumanPlayer::resetStats()
{
	Player::resetStats();
	roundsPlayed = 0;
}

// Add 1 to the number of rounds played
void HumanPlayer::incrementRoundsPlayed()
{
	roundsPlayed++;
}

