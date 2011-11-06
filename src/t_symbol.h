#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <string>
#include <QtCore/QLine>
#include <QtCore/QPoint>
#include <cstdint>

class t_wireObject;
class t_pinObject;
class t_symbolObject;

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
		std::vector<t_symbolObject*>	items;
//		std::vector<t_pinObject>		pins;
	private:
		uint16_t						wireNames, pinNames;
};

class t_symbolObject
{
	public:
		std::string						name;
		uint8_t							type;
		bool							selected;
		virtual							~t_symbolObject(void);
		    							t_symbolObject(void);
		virtual QLine					getData(void) = 0;
};

class t_wireObject : public t_symbolObject
{
	public:
		virtual							~t_wireObject(void);
										t_wireObject(void);
		virtual QLine					getData(void);
		QLine							data;
};

class t_pinObject : public t_symbolObject
{
	public:
		virtual							~t_pinObject(void);
										t_pinObject(void);
		virtual QLine					getData(void);
		QPoint							data;
};

#endif
