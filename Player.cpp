#include "Player.h"

// Default constructor
Player::Player() {
	name = "";
	resetStats();
}

// Usual creation constructor
Player::Player(std::string playerName) {
	name = playerName;
	resetStats();
}

// Virtual destructor
Player::~Player() {}


// ACCESSSOR FUNCTIONS

// Returns the player's current score
short Player::getScore() const { return score; }

// Returns the player's current consecutive wins
short Player::getConsecutiveWins() const { return consecutiveWins; }


// MUTATOR FUNCTIONS

// Resets the player's stats (score, consecutive wins, skill level, and rounds played)
void Player::resetStats()
{
	score = 0;
	consecutiveWins = 0;
}

// Adds value to the player's score
void Player::updateScore(short value)
{
	score += value;
}

// Resets the player's number of consecutive wins to 0
void Player::resetConsecutiveWins()
{
	consecutiveWins = 0;
}

// Add 1 to the player's number of consecutive wins
void Player::incrementConsecutiveWins()
{
	consecutiveWins++;
}
