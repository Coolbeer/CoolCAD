#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <string>
#include <QtCore/QLine>
#include <cstdint>

class t_wireObject;
class t_pinObject;
class symbolObject;

#define MOVE 1
#define WIRE 2
#define EDIT 4
#define PIN  8

class t_symbol
{
	public:
										t_symbol(void);
		void							addLine(QLine &line);
		void							addPin(QPoint &pos);
		bool							empty(void);
		std::vector<t_wireObject>		wires;
		std::vector<t_pinObject>		pins;
	private:
		uint16_t						wireNames, pinNames;
};

class t_symbolObject
{
	public:
		std::string						name;
		uint8_t							type;
};

class t_wireObject : public t_symbolObject
{
	public:
										t_wireObject(void);
		QLine							line;
};

class t_pinObject : public t_symbolObject
{
	public:
										t_pinObject(void);
		QPoint							position;
};

#endif
