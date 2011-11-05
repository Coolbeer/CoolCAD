#ifndef PARTEDITOR_H
#define PARTEDITOR_H

#include <QtGui/QMainWindow>

#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>

class t_partEditor : public QMainWindow
{
	Q_OBJECT
	public:
						t_partEditor(void);
		QWidget*		getViewWidget(void);
	private:
		QGraphicsView	*graphicsView;
		QGraphicsScene	*graphicsScene;
		void			drawGrid(void);
};

#endif
