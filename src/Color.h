#pragma once

#include <map>
#include <set>
#include <ostream>

enum class Color
{
	Red,
	Green,
	Blue
};

const Color cDefaultColor{ Color::Red };

const std::map<Color, std::set<Color>> cAvailableColorTransitions
{
	{Color::Green, {Color::Blue}},
	{Color::Blue, {Color::Red, Color::Green}}
};

bool static canRecolor(const Color curColor, const Color newColor)
{
	return cAvailableColorTransitions.count(curColor)
		&& cAvailableColorTransitions.at(curColor).count(newColor);
}

std::ostream& operator<<(std::ostream& os, const Color color);