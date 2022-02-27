#include <vector>
#include <iostream>
#include "src/ColorSequence.h"

struct RecolorParams
{
	Color src, dst;
	int number_of_digits;
};
const std::vector<RecolorParams> cRecolorParamsVec = {
	{Color::Green, Color::Blue, 3},
	{Color::Green, Color::Blue,	3},
	{Color::Red, Color::Blue, 3},
	{Color::Blue, Color::Red, 9},
	{Color::Green, Color::Blue,	9},
	{Color::Blue, Color::Green,	9}
};

int main()
{
	ColorSequence sequence(1, 9, Color::Green);
	std::cout << "Initial state of sequence: " << sequence << std::endl;

	for (const RecolorParams& params : cRecolorParamsVec)
	{
		sequence.recolor(params.src, params.dst, params.number_of_digits);
		std::cout << "Try recolor from '" << params.src << "'"
			<< " to '" << params.dst << "' "
			<< params.number_of_digits << " digits, result: " << sequence << std::endl;
	}
	std::cout << "Result state of sequence: " << sequence << std::endl;

	return 0;
}