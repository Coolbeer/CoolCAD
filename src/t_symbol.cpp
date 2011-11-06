#include "t_symbol.h"
#include <boost/lexical_cast.hpp>

t_symbol::t_symbol(void)
{
	wireNames = pinNames = 0;
}

void t_symbol::addLine(QLine &line)
{
	wireObject tmpWire;
	tmpWire.line = line;
	tmpWire.name = "p" + boost::lexical_cast<std::string>(wireNames);
	++wireNames;
	wires.push_back(tmpWire);
}

void t_symbol::addPin(QPoint &pos)
{
	pinObject tmpPin;
	tmpPin.position = pos;
	tmpPin.name = "w" + boost::lexical_cast<std::string>(pinNames);
	++pinNames;
	pins.push_back(tmpPin);
}


wireObject::wireObject(void)
{
	type = WIRE;
}

pinObject::pinObject(void)
{
	type = PIN;
}
