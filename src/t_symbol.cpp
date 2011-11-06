#include "t_symbol.h"

void t_symbol::addLine(QLine &line)
{
	internalLines.push_back(line);
}

