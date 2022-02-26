#pragma once

#include <optional>
#include <iostream>
#include "Color.h"

class ColorSet
{
public:
	ColorSet(const Color color, const int startNumber, const size_t size = 1);
	size_t size() const { return size_; }
	Color color() const { return color_; }
	int startNumber() const { return startNumber_; }
	void merge(const ColorSet & otherColorSet);

	using ColorSetOpt = std::optional<ColorSet>;
	using RecoloredResultPair = std::pair<ColorSetOpt, ColorSetOpt>;
	static RecoloredResultPair getRecolorResult(const Color src, const Color dst, const size_t numberOfDigitsToRecolor, const ColorSet &colorSet);

private:
	size_t size_;
	int startNumber_;
	Color color_;
};