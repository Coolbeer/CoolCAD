#include "t_symbol.h"

void t_symbol::addLine(QLine &line)
{
	internalLines.push_back(line);
}

QLine t_symbol::getLine(uint16_t pos)
{
	return internalLines.at(pos);
}