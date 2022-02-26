#pragma once

#include <map>
#include <set>

enum class Color
{
	Red,
	Green,
	Blue
};

const static std::map<Color, std::set<Color>> cAvailableColorTransitions
{
	{Color::Green, {Color::Blue}},
	{Color::Blue, {Color::Red, Color::Green}}
};

bool static canRecolor(const Color curColor, const Color newColor)
{
	return cAvailableColorTransitions.count(curColor) 
		&& cAvailableColorTransitions.at(curColor).count(newColor);
}

char static colorToChar(const Color color)
{
	switch (color)
	{
	case Color::Red:
		return 'r';
	case Color::Green:
		return 'g';
	case Color::Blue:
		return 'b';
	default:
		return '-';
	}
}