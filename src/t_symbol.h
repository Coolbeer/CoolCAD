#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <QtCore/QLine>
#include <cstdint>

class t_symbol
{
	public:
		void							addLine(QLine &line);
		bool							empty(void);
		std::vector<QLine>				internalLines;
		std::vector<QPoint>				internalPins;
};

#endif
