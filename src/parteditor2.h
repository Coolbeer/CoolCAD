#ifndef PARTEDITOR2_H
#define PARTEDITOR2_H

#include <QtGui/QWidget>
#include <cstdint>

class t_partEditor2 : public QWidget
{
	Q_OBJECT
	public:
						t_partEditor2(void);
	private:
		void			drawGrid(void);
		uint16_t		dotX;
		uint16_t		dotY;
	protected:
		void paintEvent(QPaintEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
};

#endif