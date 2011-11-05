#include "parteditor.moc"
#include <stdint.h>

t_partEditor::t_partEditor(void)
{
    graphicsView = new QGraphicsView;
    graphicsScene = new QGraphicsScene;
    graphicsView->setScene(graphicsScene);
	setCentralWidget(graphicsView);
	graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	drawGrid();
}

QWidget* t_partEditor::getViewWidget(void)
{
	return graphicsView->viewport();
}

void t_partEditor::drawGrid(void)
{
	QPen dotPen;
	dotPen.setStyle(Qt::DashLine);
	dotPen.setColor(QColor(200,200,200));
	for(int16_t x = -1000; x != 1000; x += 50)
	{
		graphicsScene->addLine(x,-1000,x,1000, dotPen);
		graphicsScene->addLine(-1000,x,1000,x, dotPen);
	}
	dotPen.setColor(QColor(100,100,100));
	graphicsScene->addLine(0,-10,0,10, dotPen);
	graphicsScene->addLine(-10,0,10,0, dotPen);
}
