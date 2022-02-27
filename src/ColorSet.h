#pragma once

#include <optional>
#include "Color.h"

class ColorSet
{
public:
	const static Color cDefaultColor = Color::Red;
	const static int cDefaultStartNumber = 1;
	const static size_t cDefaultSize = 1;

	ColorSet();
	ColorSet(const Color color, const int startNumber, const size_t size = 1);

	Color color() const { return color_; }
	int startNumber() const { return startNumber_; }
	size_t size() const { return size_; }
	void merge(const ColorSet & otherColorSet);

	bool operator==(const ColorSet& rhs) const;

	using ColorSetOpt = std::optional<ColorSet>;
	using RecoloredResultPair = std::pair<ColorSetOpt, ColorSetOpt>;
	static RecoloredResultPair getRecolorResult(const Color src, const Color dst, const size_t numberOfDigitsToRecolor, const ColorSet &colorSet);

private:
	Color color_;
	int startNumber_;
	size_t size_;
};