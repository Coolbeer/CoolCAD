#ifndef PARTEDITOR2_H
#define PARTEDITOR2_H

#include <QtGui/QWidget>

class t_partEditor2 : public QWidget
{
	Q_OBJECT
	public:
						t_partEditor2(void);
	private:
		void			drawGrid(void);
	protected:
		void paintEvent(QPaintEvent *event);
};

#endif