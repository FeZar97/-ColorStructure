#pragma once

#include <list>
#include "ColorSet.h"

class ColorSequence
{
public:
	ColorSequence(const int n, const int m, const Color color);

	/*
	available result values:
		0 - success;
		1 - unavailable pair of src and dst colors;
		2 - invalid value of 'number_of_digits';
		3 - not a single number could be recolored;
	*/
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
	void checkNeighbours(const ColorSet::RecoloredResultPair &recolorResult,
						 const ColorListIterPair &insertRes);

private:
	ColorMap orderedColors_;
	ColorList sequence_;
};

