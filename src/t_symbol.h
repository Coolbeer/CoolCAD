#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <QtCore/QLine>

class t_symbol
{
	public:
		void					addLine(QLine &line);

	private:
		std::vector<QLine>		internalLines;
};

#endif
