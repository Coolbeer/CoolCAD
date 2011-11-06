#ifndef PARTEDITOR2_H
#define PARTEDITOR2_H

#include <QtGui/QWidget>
#include <cstdint>

#include "t_symbol.h"
#include "t_infoWindow.h"

#define MOVE 1
#define LINE 2
#define EDIT 4
#define PIN  8
#define INFO 16

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
		int16_t				dotX, dotY;
		int16_t				startDotX, startDotY;
		uint8_t				mode;
		double				scale;
		uint8_t				toolBarButton;
		t_symbol			*symbol;
		uint16_t			translateMouse(uint16_t);
		t_infoWindow		*infoWindow;
	protected:
		void				paintEvent(QPaintEvent *event);
		void				mouseMoveEvent(QMouseEvent *event);
		void				mousePressEvent(QMouseEvent *event);
		void				wheelEvent (QWheelEvent *event); 
};

#endif
