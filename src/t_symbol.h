#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <string>
#include <QtCore/QLine>
#include <cstdint>

class wireObject;
class pinObject;
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
		std::vector<wireObject>			wires;
		std::vector<pinObject>			pins;
	private:
		uint16_t						wireNames, pinNames;
};

class symbolObject
{
	public:
		std::string						name;
		uint8_t							type;
};

class wireObject : public symbolObject
{
	public:
										wireObject(void);
		QLine							line;
};

class pinObject : public symbolObject
{
	public:
										pinObject(void);
		QPoint							position;
};

#endif
