#ifndef PARTEDITOR2_H
#define PARTEDITOR2_H

#include <QtGui/QWidget>
#include <cstdint>

#include "t_symbol.h"

#define MOVE 1
#define LINE 2
#define EDIT 4

class t_partEditor2 : public QWidget
{
	Q_OBJECT
	public:
							t_partEditor2(void);
		uint16_t			roundNumber(uint16_t number);
		void				cancel(void);
		void				setToolBarButton(uint8_t number);
	private:
		void				drawGrid(void);
		uint16_t			dotX, dotY;
		uint16_t			startDotX, startDotY;
		uint8_t				mode;
		double				scale;
		uint8_t				toolBarButton;
		t_symbol			*symbol;
	protected:
		void				paintEvent(QPaintEvent *event);
		void				mouseMoveEvent(QMouseEvent *event);
		void				mousePressEvent(QMouseEvent *event);
		void				wheelEvent (QWheelEvent *event); 
};

#endif
