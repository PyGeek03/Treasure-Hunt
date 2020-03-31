#include "MasterMind.h"

// CONSTRUCTOR
MasterMind::MasterMind() {
	playerQuitted = false;
	resetGame(); 
}

// DESTRUCTOR
MasterMind::~MasterMind() {}


// ACCESSOR FUNCTIONS

// Returns a constant reference to the player
const HumanPlayer& MasterMind::getPlayer() const { return player; }

// Returns a constant reference to the game board
const Board& MasterMind::getBoard() const { return board; }

// Returns a constant reference to the computer player (genie)
const Genie& MasterMind::getGenie() const { return genie; }

// Returns current round's secret code
std::string MasterMind::getCode() const { return code; }

// Returns the filename of the introduction text file
std::string MasterMind::getIntroFile() const { return introFile; }

// Returns the name of the player's level
std::string MasterMind::getPlayerLevel() const { return levels[player.getLevel()]; }

// Returns the number of rounds left
short MasterMind::getRoundsLeft() const { return MAX_ROUNDS - getCurrentRound(); }

// Returns the current round number
short MasterMind::getCurrentRound() const
{
	if (roundEnded) return player.getRoundsPlayed();
	else return player.getRoundsPlayed() + 1;
}

// Returns the code range matching player's level
short MasterMind::getCodeRange() const { return codeRange[player.getLevel()]; }

// Returns the code length matching player's level
size_t MasterMind::getCodeLength() const { return codeLength[player.getLevel()]; }

// Returns an appropriate random genie's comment
std::string MasterMind::getGenieComment() const
{
	size_t totalGuesses = board.getCurrentRows();
	if (totalGuesses == 0) return "";
	else if (lastRightSlots >= totalGuesses) return genie.getComment(GOOD);
	else if (lastRightSlots*2 >= totalGuesses) return genie.getComment(AVERAGE);
	else if (consecutiveBadGuesses >= 3) return genie.getComment(BAD);
	else return "";
}

// Checks if the round has ended
bool MasterMind::roundNotEnd() const { return !roundEnded; }

// Checks if player quitted or all rounds have been played
bool MasterMind::gameNotEnd() const {
	return (!playerQuitted) && (MAX_ROUNDS - getCurrentRound() > 0);
}

// Returns the name of the winner, or "Draw" if no one wins
std::string MasterMind::getWinnerName() const {
	if (winner != NULL)	return winner->getName();
	else return "Draw";
}

// Return how many points the winner earned
short MasterMind::getWinnerEarning() const { return winnerEarning; }


// MUTATOR FUNCTIONS

// When there's a new player, sets the player's name and level,
// and sets the board's max number of rows and guess' length
void MasterMind::newPlayer(std::string name, short level)
{
	player = HumanPlayer(name, level);
	board = Board(maxGuesses[level], codeLength[level]);
}

// Starts a new round
void MasterMind::newRound()
{
	resetRound();
	short level = player.getLevel();
	code = genie.newCode(codeLength[level], codeRange[level]);
}

// Processes player's new guess
void MasterMind::newGuess(std::string guess)
{
	// computes the feedback
	Feedback feedback = computeFeedback(guess);

	// adds guess and feedback to board
	board.addRow(BoardRow(guess, feedback));

	// for fetching Genie's comment and calculate round scores
	if (feedback.getRightSlots() <= lastRightSlots) {
		consecutiveBadGuesses++;
	}
	else {
		totalBadGuesses += consecutiveBadGuesses;
		consecutiveBadGuesses = 0;
	}
	lastRightSlots = feedback.getRightSlots();

	// check if round has ended, and end it if yes
	roundEnded = roundHasEnded();
	if (roundEnded) endRound();
}

// Resets the game
void MasterMind::resetGame()
{
	resetRound();
	player.resetStats();
	genie.resetStats();
}

// Player quits the game
void MasterMind::quit()
{
	playerQuitted = true;
	roundEnded = true;
}

// PRIVATE FUNCTIONS

// Resets all game variables for a new round
void MasterMind::resetRound()
{
	board.emptyBoard();
	code = "";
	roundEnded = false;
	lastRightSlots = 0;
	consecutiveBadGuesses = 0;
	totalBadGuesses = 0;
	winnerEarning = 0;
}

// Checks round ending conditions
bool MasterMind::roundHasEnded()
{
	if (lastRightSlots == code.length()) {
		// the player has won this round!
		winner = &player;
		return true;
	}
	else if (board.getUnusedGuesses() == 0) {
		// the player has lost this round
		winner = &genie;
		return true;
	}
	else {
		return false;
	}
}

// Ends a round
void MasterMind::endRound()
{
	player.incrementRoundsPlayed();

	short bonus = 0;
	if (winner == &player) {
		genie.resetConsecutiveWins();
		bonus = board.getUnusedGuesses();
	}
	else {
		player.resetConsecutiveWins();
		bonus = totalBadGuesses;
	}

	winner->incrementConsecutiveWins();
	if (winner->getConsecutiveWins() >= 3) {
		bonus += 10;
	}
	winnerEarning = 3 * code.length() + bonus;
	winner->updateScore(winnerEarning);
}

// Ends a game by selecting the ultimate winner
void MasterMind::endGame()
{
	short playerScore = player.getScore();
	short genieScore = genie.getScore();

	if (playerScore > genieScore) { winner = &player; }
	else if (playerScore < genieScore) { winner = &genie; }
	else winner = NULL;
}

// Computes the feedback, based on player's guess
Feedback MasterMind::computeFeedback(std::string guess)
{
	short rightSlots = 0;  // counts correct digits at correct slots
	short wrongSlots = 0;  // counts correct digits at wrong slots

	std::string scrambledCode = "";   // code without correct digits at correct slots
	std::string scrambledGuess = "";  // guess without correct digits at correct slots

	// counts how many digits player guessed right at correct slots,
	// and keeps track of the other digits
	for (size_t i = 0; i < code.length(); i++) {
		if (code[i] == guess[i]) {
			rightSlots++;
		}
		else {
			scrambledCode += code[i];
			scrambledGuess += guess[i];
		}
	}

	short tally[10] = { 0 };  // array of 10 zeroes
	// tallies up how many of which digits are in scrambledCode
	for (size_t i = 0; i < scrambledCode.length(); i++) {
		short digit = scrambledCode[i] - '0';
		tally[digit]++;
	}
	// counts how many digits player guess right but put in wrong slots
	for (size_t i = 0; i < scrambledGuess.length(); i++) {
		short digit = scrambledGuess[i] - '0';
		if (tally[digit] > 0) {
			wrongSlots++;
			tally[digit]--;
		}
	}

	return Feedback(rightSlots, wrongSlots);
}
