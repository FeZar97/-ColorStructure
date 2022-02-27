#include "ColorSet.h"

ColorSet::ColorSet(): ColorSet(cDefaultColor, cDefaultStartNumber, cDefaultSize)
{}

ColorSet::ColorSet(const Color color, const int startNumber, const size_t size):
	color_(color), startNumber_(startNumber), size_(size)
{}

void ColorSet::merge(const ColorSet & otherColorSet)
{
	if (color_ != otherColorSet.color())
	{
		return;
	}

	size_ += otherColorSet.size();

	startNumber_ = std::min(startNumber_, otherColorSet.startNumber());
}

bool ColorSet::operator==(const ColorSet& rhs) const
{
	return color_ == rhs.color()
		&& startNumber_ == rhs.startNumber()
		&& size_ == rhs.size();
}

ColorSet::RecoloredResultPair ColorSet::getRecolorResult(const Color src, const Color dst, const size_t numberOfDigitsToRecolor, const ColorSet & colorSet)
{
	if (!canRecolor(src, dst) || src != colorSet.color())
	{
		return { std::nullopt, std::nullopt };
	}

	if (numberOfDigitsToRecolor >= colorSet.size())
	{
		return { ColorSet{dst, colorSet.startNumber(), colorSet.size()},
				 std::nullopt };
	}
	else
	{
		return { ColorSet{dst, colorSet.startNumber(), numberOfDigitsToRecolor},
				 ColorSet{src, colorSet.startNumber() + static_cast<int>(numberOfDigitsToRecolor), colorSet.size() - numberOfDigitsToRecolor} };
	}
}