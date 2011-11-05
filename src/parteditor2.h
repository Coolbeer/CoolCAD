#ifndef PARTEDITOR2_H
#define PARTEDITOR2_H

#include <QtGui/QWidget>
#include <cstdint>

#define NORMAL 0
#define LINE   1

class t_partEditor2 : public QWidget
{
	Q_OBJECT
	public:
							t_partEditor2(void);
		uint16_t			roundNumber(uint16_t number);
	private:
		void				drawGrid(void);
		uint16_t			dotX, dotY;
		uint16_t			startDotX, startDotY;
		uint8_t				mode;
	protected:
		void paintEvent(QPaintEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void mousePressEvent(QMouseEvent *event);
};

#endif
