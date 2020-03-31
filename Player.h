#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player { // abstract class
public:
	// Constructors
	Player();
	Player(std::string playerName);

	// Virtual destructor
	virtual ~Player();

	// Accessor functions

	virtual std::string getName() const = 0;
	short getScore() const;
	short getConsecutiveWins() const;


	// Mutator functions

	virtual void resetStats();
	void updateScore(short value);
	void resetConsecutiveWins();
	void incrementConsecutiveWins();


protected:
	// Variables
	std::string name;
	short score;
	short consecutiveWins;
};

#endif // !PLAYER_H
