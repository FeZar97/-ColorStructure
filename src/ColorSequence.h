#pragma once

#include <list>
#include "ColorSet.h"

class ColorSequence
{
public:
	ColorSequence(const size_t n = cDefaultStartNumber, const size_t m = cDefaultStartNumber, const Color color = cDefaultColor);

	enum RecolorResultVal
	{
		SUCCESS,
		UNAVALAIBLE_COLOR_PAIR, // unavailable pair of 'src' and 'dst' colors
		INVALID_DIGITS_ARG, // invalid value of 'number_of_digits'
		NOTHING_TO_RECOLOR // not a single digit could be recolored
	};
	int recolor(Color src, Color dst, int number_of_digits);

	friend std::ostream& operator<<(std::ostream& os, const ColorSequence& sequence);

private:
	using ColorList = std::list<ColorSet>;
	using ColorListIter = ColorList::iterator;
	using SizeMap = std::map<size_t, ColorListIter>;
	using ColorMap = std::map<Color, SizeMap>;
	using ColorListIterPair = std::pair<ColorListIter, ColorListIter>;

	void addRecolorResult(const ColorSet::RecoloredResultPair& recolorResult,
						ColorListIter posToInsert,
						ColorListIterPair& insertRes);
	void checkNeighbours(const ColorSet::RecoloredResultPair& recolorResult,
						 const ColorListIterPair& insertRes);

private:
	ColorMap orderedColors_;
	ColorList sequence_;
};