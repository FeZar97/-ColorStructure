#pragma once

#include <optional>
#include "Color.h"

const size_t cDefaultStartNumber{ 1 }, cDefaultSize{ 1 };

class ColorSet
{
public:
	ColorSet(const Color color = cDefaultColor, const size_t startNumber = cDefaultStartNumber, const size_t size = cDefaultSize);

	Color color() const { return color_; }
	size_t startNumber() const { return startNumber_; }
	size_t size() const { return size_; }

	void merge(const ColorSet& otherColorSet);
	bool operator==(const ColorSet& rhs) const;

	using ColorSetOpt = std::optional<ColorSet>;
	using RecoloredResultPair = std::pair<ColorSetOpt, ColorSetOpt>;
	static RecoloredResultPair getRecolorResult(const Color src, const Color dst, const size_t numberOfDigitsToRecolor, const ColorSet& colorSet);

private:
	Color color_;
	size_t startNumber_, size_;
};