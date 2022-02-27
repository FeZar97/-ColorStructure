#include "Color.h"

std::ostream& operator<<(std::ostream& os, const Color color)
{
	switch (color)
	{
	case Color::Red:
		os << 'r';
		break;
	case Color::Green:
		os << 'g';
		break;
	case Color::Blue:
		os << 'b';
		break;
	default:
		os << '-';
	}
	return os;
}