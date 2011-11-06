#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <QtCore/QLine>
#include <cstdint>

class t_symbol
{
	public:
		void							addLine(QLine &line);
		QLine							getLine(uint16_t pos);
		void							removeLine(uint16_t pos);
		bool							empty(void);
		std::vector<QLine>::iterator	begin(void);
		std::vector<QLine>::iterator	end(void);

	private:
		std::vector<QLine>				internalLines;
};

#endif
