#include "ColorSequence.h"

int main()
{
	ColorSequence sequence(1, 9, Color::Green);
	std::cout << "[MAIN] " << sequence << std::endl; // 1g 2g 3g 4g 5g 6g 7g 8g 9g

	sequence.recolor(Color::Green, Color::Blue, 3);
	std::cout << "[MAIN] " << sequence << std::endl; // 1b 2b 3b 4g 5g 6g 7g 8g 9g

	sequence.recolor(Color::Green, Color::Blue, 3);
	std::cout << "[MAIN] " << sequence << std::endl; // 1b 2b 3b 4b 5b 6b 7g 8g 9g
	
	sequence.recolor(Color::Red, Color::Blue, 3);
	std::cout << "[MAIN] " << sequence << std::endl; // 1b 2b 3b 4b 5b 6b 7g 8g 9g
	
	sequence.recolor(Color::Blue, Color::Red, 9);
	std::cout << "[MAIN] " << sequence << std::endl; // 1r 2r 3r 4r 5r 6r 7g 8g 9g

	sequence.recolor(Color::Green, Color::Blue, 9);
	std::cout << "[MAIN] " << sequence << std::endl; // 1r 2r 3r 4r 5r 6r 7b 8b 9b

	sequence.recolor(Color::Blue, Color::Green, 9);
	std::cout << "[MAIN] " << sequence << std::endl; // 1r 2r 3r 4r 5r 6r 7g 8g 9g

	return 0;
}