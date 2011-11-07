#include "t_symbol.h"
#include <boost/lexical_cast.hpp>

t_symbol::t_symbol(void)
{
	wireNames = pinNames = 0;
}

void t_symbol::addLine(QLine &line)
{
	t_wireObject *tmpWire = new t_wireObject;
	tmpWire->data = line;
	tmpWire->name = "p" + boost::lexical_cast<std::string>(wireNames);
	++wireNames;
	items.push_back(tmpWire);
}

void t_symbol::addPin(QPoint &pos)
{
	t_pinObject *tmpPin = new t_pinObject;
	tmpPin->data = pos;
	tmpPin->name = "w" + boost::lexical_cast<std::string>(pinNames);
	++pinNames;
	items.push_back(tmpPin);
}


t_wireObject::t_wireObject(void)
{
	type = WIRE;
	selected = false;
}

t_pinObject::t_pinObject(void)
{
	type = PIN;
	selected = false;
}


t_symbolObject::~t_symbolObject(void)
{

}

t_symbolObject::t_symbolObject(void)
{

}

t_wireObject::~t_wireObject(void)
{

}

t_pinObject::~t_pinObject(void)
{

}

QLine t_wireObject::getData(void)
{
	return data;
}

QLine t_pinObject::getData(void)
{
	return QLine(data, data);
}
