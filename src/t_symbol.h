#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <QtCore/QLine>
#include <cstdint>

class t_symbol
{
	public:
		void					addLine(QLine &line);
		QLine					getLine(uint16_t pos);
	private:
		std::vector<QLine>		internalLines;
};

#endif
