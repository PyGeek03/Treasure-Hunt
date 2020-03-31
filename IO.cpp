#include "IO.h"

IO::IO() {}

IO::~IO() {}

// Starts a new game!
void IO::newGame()
{
	// display game introduction, and ask for player's name and level
	displayIntro();

	std::string nameQuestion = " First, what's your name, challenger? ";
	std::string levelQuestion = " And what's your skill level? (1-3): ";

	// print title again before asking for player's name and level
	displayTitle(std::max(nameQuestion.length(), levelQuestion.length()) + 10);
	std::cout << " - Genie:\n" << std::endl;
	std::string name = askForString(nameQuestion);
	short level = askForNumber(levelQuestion, 1, 3);

	// set new player
	game.newPlayer(name, level);

	// print welcome message, and ask if player wants to continue
	std::cout << " Are you ready " + player.getName() + " the " + game.getPlayerLevel() + "?" << std::endl << std::endl;
	std::string question = " Enter [y] to continue, or [n] to quit: ";
	char choice = askForLetter(question, "YNyn");
	if (choice == 'Y' || choice == 'y')
		gameLoop();
	else
		playerQuits();
}

// The main game loop
void IO::gameLoop()
{
	while (game.gameNotEnd()) {
		// play a new round
		game.newRound();
		// round loop
		while (game.roundNotEnd()) {
			// ask for and process player's guess
			std::string guess = askForGuess();
			if (guess == "quit") {
				playerQuits();
				return;
			}
			else {
				game.newGuess(guess);
			}
		}
		// reveal secret code
		displayBoard();
		std::cin.get();

		// display results, and ask if player wants to continue
		displayResults();
	}
}

// Clears the screen and displays the title of the game
// The title would be centre-aligned using argument screenWidth
void IO::displayTitle(size_t screenWidth)
{
	std::string title = "MasterMind::Treasure Hunt";

	if (screenWidth < title.length())
		screenWidth = title.length();

    std::cout << std::string(100, '\n');

	std::cout << " " << std::string(screenWidth, '~') << std::endl;
	printCentred(title, screenWidth);
	std::cout << " " << std::string(screenWidth, '~') << std::endl;
	std::cout << std::endl;
}

// Displays the introduction file
void IO::displayIntro() {
	// declare and initialize local variables
    std::ifstream fileToRead(game.getIntroFile());
	std::stringstream fileContent;
	size_t maxLineLength = 0;

	// read the file, add to fileContent,
	// and find the length of the longest line
	if (fileToRead.is_open()) {
		std::string line = "";
		while (!fileToRead.eof()) {
			getline(fileToRead, line);

			fileContent << "  " << line << std::endl;

			size_t lineLength = line.length();
			if (lineLength > maxLineLength) {
				maxLineLength = lineLength;
			}
		}
	}
	fileToRead.close();

	// centre-align the title to match the longest line
	displayTitle(maxLineLength);
	std::cout << fileContent.str();
	std::cin.get();
}

// Gets the display width of the guess column
size_t IO::getGuessWidth()
{
	return 6 * board.getGuessLen() + 3;
}

// Gets the display width of the feedback column
size_t IO::getFeedbackWidth()
{
	return feedbackHeader.length();
}

// Gets the display width of the whole board
size_t IO::getBoardWidth() 
{ 
	return getGuessWidth() + getFeedbackWidth() + 3; 
}

// Formats a player's guess for displaying
std::string IO::formatGuess(std::string guess)
{
	std::stringstream formattedGuess;
	for (std::string::const_iterator it = guess.begin(); it != guess.end(); ++it)
	{
		formattedGuess << " | " << *it << " |";  // print each character in guess in an ASCII "box"
	}

	return formattedGuess.str();
}

// Formats a feedback for displaying
std::string IO::formatFeedback(Feedback feedback)
{
	std::string feedbackString = multiplyStr(feedback.getRightSlots(), "o ") + multiplyStr(feedback.getWrongSlots(), "x ");
	feedbackString += std::string(getFeedbackWidth() - feedbackString.length() - 2, ' ');  // pad feedback string to the right with spaces
	feedbackString = "  " + feedbackString;
	return feedbackString;
}

// Displays a board row
void IO::displayRow(std::string formattedGuess, std::string formattedFeedback)
{
	size_t guessLen = board.getGuessLen();
	size_t feedbackWidth = getFeedbackWidth();
	std::cout << " | " << multiplyStr(guessLen, " .---.") << "  |" << std::string(feedbackWidth, ' ') << '|' << std::endl;
	std::cout << " | " << formattedGuess                  << "  |" << formattedFeedback          << '|' << std::endl;
	std::cout << " | " << multiplyStr(guessLen, " '---'") << "  |" << std::string(feedbackWidth, ' ') << '|' << std::endl;
	std::cout << " +" << std::string(getGuessWidth(), '-') << '+' << std::string(feedbackWidth, '-') << '+' << std::endl;
}

// Displays the title, the current round and the game board;
void IO::displayBoard()
{
	size_t guessLen = board.getGuessLen();

	// print title and current round
	displayRound();

	// print the first row separator
	std::cout << " +" << std::string(getGuessWidth(), '-') << '+' << std::string(getFeedbackWidth(), '-') << '+' << std::endl;

	// print header row
	if (game.roundNotEnd()) {
		std::string codePlaceholder = formatGuess(std::string(guessLen, '?'));
		displayRow(codePlaceholder, feedbackHeader);
	}
	else {
		std::string revealedCode = formatGuess(game.getCode());
		displayRow(revealedCode, feedbackHeader);
	}

	// print all rows
	const std::vector<BoardRow>& allRows = board.getAllRows();
	std::vector<BoardRow>::const_iterator iterRow = allRows.begin();
	while (iterRow != allRows.end()) {
		std::string guess = formatGuess(iterRow->getGuess());
		std::string feedback = formatFeedback(iterRow->getFeedback());
		displayRow(guess, feedback);
		iterRow++;
	}

	std::cout << std::endl;
}

// Displays the title and the round, as aligned to the board
void IO::displayRound()
{
	// print game title
	displayTitle(getBoardWidth());

	// print current round
	std::string roundLine = "Round " + std::to_string(game.getCurrentRound()) + " ";
	printCentred(roundLine, getBoardWidth());
}

// Displays the prompt to ask for player's guess
void IO::displayGeniePrompt()
{
	std::cout << " - Genie: " << game.getGenieComment() << std::endl;
	std::cout << " Possible digits: ";
	for (short i = 0; i != 1 + game.getCodeRange(); i++)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl << " Your guesses left: " << board.getUnusedGuesses() << std::endl << std::endl;
}

// Displays results of the last round, and ask if player wants to continue playing
void IO::displayResults()
{
	// initialize some important strings
    std::string question = "";
	if (game.gameNotEnd())
		question = " Do you want to continue, " + player.getName() + "? (y/n): ";
	else
		question = " Do you want to play again, " + player.getName() + "? (y/n): ";

	std::string playerResult = player.getName() + ": " + std::to_string(player.getScore());
    std::string genieResult = genie.getName() + ": " + std::to_string(genie.getScore());

	// print title and the last round
	displayRound();

	// determine margin and gap to print player's and genie's score nicely
	size_t marginLength = 4;
	size_t gapLength = getBoardWidth() - playerResult.length() - genieResult.length() - marginLength * 2 ;
    std::string margin = std::string(marginLength, ' ');
	std::string gap = std::string(gapLength, ' ');
	 
	// print player's and genie's score
	std::cout << margin << playerResult << gap << genieResult << std::endl << std::endl;

	if (game.gameNotEnd()) {
		// print the round's winner!
		std::cout << margin << game.getWinnerName() << " won round " << game.getCurrentRound();
		std::cout << " scoring " << game.getWinnerEarning() << std::endl << std::endl;

		// print number of rounds left
		short roundsLeft = game.getRoundsLeft();
		// "rounds" (in plural) if roundsLeft > 1, "round" (singular) otherwise
		std::cout << margin << roundsLeft << " more round" << std::string(roundsLeft > 1, 's') << " to go!" << std::endl << std::endl;
		std::cout << " " << std::string(getBoardWidth(), '~') << std::endl << std::endl;

		// ask if player wants to continue
		char choice = askForLetter(question, "YNyn");
		if (choice == 'N' || choice == 'n')
			playerQuits();
	}
	else {
		// print the game's ultimate winner! (If there is one)
		std::string finalResult = "";

		if (game.getWinnerName() != "Draw")
			finalResult = game.getWinnerName() + " has won the treasure!";
		else
			finalResult = "It's a draw!";

		std::cout << margin << finalResult << std::endl << std::endl;
		std::cout << " " << std::string(getBoardWidth(), '~') << std::endl << std::endl;

		// ask if the player wants to play again
		char choice = askForLetter(question, "YNyn");
		if (choice == 'Y' || choice == 'y') {
			game.resetGame();
			gameLoop();  // runs gameLoop again
		}
		else {
			playerQuits();
		}
	}
}

// Displays the board and asks for player's guess
std::string IO::askForGuess()
{
	displayBoard();
	displayGeniePrompt();

	std::string guess = "";
	bool invalidInput = true;
	while (invalidInput) {
		guess = askForString(" Make a guess, or [quit] if you can't: ");
		if (validGuess(guess)) 
			invalidInput = false;
		else 
			std::cout << " Invalid input. Please try again.\n" << std::endl;
	}
	
	return removeWhiteSpace(guess);
}

// Quits the game, and displays quit message when the player choose to quits
void IO::playerQuits()
{
	game.quit();

    std::string quitMessage = "";
	if (game.getRoundsLeft() > 0)
		quitMessage = " - Genie: The treasure is all mine now. Thanks a lot!";
	else
		quitMessage = " - Genie: That was a great game. See you later, my worthy challenger!";

	displayTitle(quitMessage.length());
	std::cout << quitMessage << std::endl << std::endl;
}

// Centre-aligns the line according to view width
void IO::printCentred(std::string line, size_t viewWidth)
{
	std::cout << " " << std::string((viewWidth - line.length()) / 2, ' ') << line << std::endl;
}

// Checks if user input at guess prompt is valid or not
bool IO::validGuess(std::string guess)
{
	size_t guessLength = removeWhiteSpace(guess).length();
	bool validGuess = guessLength == game.getCodeLength() && validDigits(removeWhiteSpace(guess));
	bool validQuit = trimWhiteSpace(guess) == "quit";
	return validGuess || validQuit;
}

// Multiplies a string a number of times
std::string IO::multiplyStr(size_t times, std::string s)
{
	std::string result = "";
	for (size_t i = times; i != 0; i--)
		result += s;
	return result;
}

// Returns the string with all whitespace removed
std::string IO::removeWhiteSpace(std::string s)
{
	std::string new_s = "";
	for (size_t i = 0; i < s.length(); i++)
	{
		if (!isspace(s[i]))
			new_s += s[i];
	}
	return new_s;
}

// Trims beginning and trailing whitespace
std::string IO::trimWhiteSpace(std::string s)
{
	size_t i = 0;
	while (isspace(s[i])) i++;

	size_t j = s.length() - 1;
	while (isspace(s[j])) j--;

	return s.substr(i, j - i + 1);
}

// Checks if player's guess consists of only digit within the code's range
bool IO::validDigits(std::string input)
{
	for (size_t i = 0; i < input.length(); i++) {
		if (charToShort(input[i]) > game.getCodeRange() or charToShort(input[i]) < 0)
			return false;
	}
	return true;
}

// Converts a digit in char to short, 
// by subtracting the ascii value of '0' from the ascii value of the char
short IO::charToShort(char c) { return c - '0'; }

// Asks user to input a string
std::string IO::askForString(std::string question)
{
	std::string userInput = "";
	while (userInput == "") {
		std::cout << question;
		ws(std::cin);  // ignore all whitespace still in input buffer, left behind by previous call to getline()
		getline(std::cin, userInput);
		std::cout << std::endl;
	}
	return userInput;
}

// Asks user to input an integer
int IO::askForNumber(std::string question, int min, int max)
{
	// declare and initialize local variables
	std::string userInput = "";
	int number = 0;
	bool invalidInput = true;

	// get user input and validate it before returning
	while (invalidInput) {
		std::cout << question;
		std::cin >> userInput;
		std::cout << std::endl;

		try {
			// try converting user input to an int
			number = stoi(userInput);
			if (min <= number && number <= max) invalidInput = false; // conversion successful, and input is in range
		}
		catch (...) { 
			invalidInput = true; // user input cannot be converted to an int, which means it's invalid
		}

		if (invalidInput) {
			// user input invalid => flush the input buffer for new input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore as many characters as possible, or until a newline character
			std::cout << " Invalid input. Please try again.\n" << std::endl;
		}
	}
	return number;
}

// Asks user to input a character
char IO::askForLetter(std::string question, std::string validOptions)
{
	// local variables
	char userInput = 0;
	bool invalidInput = true;

	// get user input and validate it before returning
	while (invalidInput) {
		std::cout << question;
		std::cin >> userInput;
		std::cout << std::endl;

		if (validOptions.find(userInput) != std::string::npos) {
			invalidInput = false;  // user input is in valid options
		}
		else {
			// user input is not in valid options => flush the input buffer for new input
			std::cin.ignore(100000, '\n'); // ignore next 100000 characters at most, or until a newline character
			std::cout << " Invalid input. Please try again.\n" << std::endl;
		}
	}
	return userInput;
}
