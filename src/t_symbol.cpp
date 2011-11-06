#include "t_symbol.h"

void t_symbol::addLine(QLine &line)
{
	internalLines.push_back(line);
}

QLine t_symbol::getLine(uint16_t pos)
{
	return internalLines.at(pos);
}

bool t_symbol::empty(void)
{
	return internalLines.empty();
}

std::vector<QLine>::iterator t_symbol::begin()
{
	return internalLines.begin();
}

std::vector<QLine>::iterator t_symbol::end()
{
	return internalLines.end();
}
