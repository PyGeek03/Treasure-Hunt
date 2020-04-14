#include <ctime>
#include "IO.h" 

int main() {
    // seed randoms
    srand(unsigned(time(NULL)));

    // create new game interface
    IO io;

    // play a new game!
    io.newGame();

    // exit
    std::cin.get(); // pause
    return 0;
}
