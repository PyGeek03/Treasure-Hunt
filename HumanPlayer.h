#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
public:
	// Constructors
	HumanPlayer();
	HumanPlayer(std::string name, short level);

	// Destructor
	~HumanPlayer();


	// Accessor functions

	std::string getName() const;
	short getLevel() const;
	short getRoundsPlayed() const;


	// Mutator functions

	void resetStats();
	void incrementRoundsPlayed();

private:
	short skillLevel;
	short roundsPlayed;
};

#endif // !HUMANPLAYER_H
