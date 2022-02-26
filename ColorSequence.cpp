#include <iostream>
#include "ColorSequence.h"

ColorSequence::ColorSequence(const int n, const int m, const Color color)
{
	size_t size = std::max(m - n + 1, 1);

	sequence_.push_back({ color, n, size });
	orderedColors_.insert({ color, {{ size, sequence_.begin() }} });
}

int ColorSequence::recolor(Color src, Color dst, int number_of_digits)
{
	if (!canRecolor(src, dst))
	{
		return 1;
	}

	if (number_of_digits <= 0)
	{
		return number_of_digits < 0 ? 2 : 0;
	}

	auto selectedColorMapIter = orderedColors_.find(src);
	if (selectedColorMapIter == orderedColors_.end())
	{
		return 3;
	}

	size_t numbersToRecolor = number_of_digits;
	auto& selectedSizeMap = selectedColorMapIter->second;
	auto selectedSizeMapIter = selectedSizeMap.lower_bound(numbersToRecolor);
	if (selectedSizeMapIter == selectedSizeMap.end())
	{
		selectedSizeMapIter = prev(selectedSizeMap.end());
		numbersToRecolor = selectedSizeMapIter->second->size();
	}
	
	ColorSet::RecoloredResultPair recolorResult = ColorSet::getRecolorResult(src, dst, numbersToRecolor, *selectedSizeMapIter->second);
	ColorListIterPair insertResPair{ sequence_.begin(), prev(sequence_.end()) };

	addRecolorResult(recolorResult, selectedSizeMapIter->second, insertResPair);

	sequence_.erase(selectedSizeMapIter->second);
	selectedSizeMap.erase(selectedSizeMapIter);

	checkNeighbours(recolorResult, insertResPair);

	return 0;
}

void ColorSequence::addRecolorResult(const ColorSet::RecoloredResultPair& recolorResult, 
									ColorListIter posToInsert, 
									ColorListIterPair& insertRes)
{
	if (recolorResult.first.has_value())
	{
		insertRes.first = sequence_.insert(posToInsert, *recolorResult.first);
		orderedColors_[recolorResult.first->color()][recolorResult.first->size()] = insertRes.first;
	}
	if (recolorResult.second.has_value())
	{
		insertRes.second = sequence_.insert(posToInsert, *recolorResult.second);
		orderedColors_[recolorResult.second->color()][recolorResult.second->size()] = insertRes.second;
	}
}

void ColorSequence::checkNeighbours(const ColorSet::RecoloredResultPair& recolorResult,
									const ColorListIterPair& insertRes)
{
	if (recolorResult.first.has_value() 
		&& insertRes.first != sequence_.begin()
		&& (*prev(insertRes.first)).color() == (*insertRes.first).color())
	{
		(*insertRes.first).merge(*prev(insertRes.first));
		sequence_.erase(prev(insertRes.first));
	}
	if (recolorResult.second.has_value() 
		&& insertRes.second != prev(sequence_.end())
		&& (*next(insertRes.second)).color() == (*insertRes.second).color())
	{
		(*insertRes.second).merge(*next(insertRes.second));
		sequence_.erase(next(insertRes.second));
	}
}

std::ostream& operator<<(std::ostream& os, const ColorSequence& sequence)
{
	for (const ColorSet& colorSet : sequence.sequence_)
	{
		char colorChar = colorToChar(colorSet.color());
		for (int number = colorSet.startNumber(); number < colorSet.startNumber() + colorSet.size(); number++)
		{
			os << number << colorChar;
		}
	}
	return os;
}