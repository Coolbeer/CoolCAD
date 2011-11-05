#include "parteditor2.moc"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <cstdint>
#include <iostream>

t_partEditor2::t_partEditor2(void)
{
}

void t_partEditor2::drawGrid(void)
{

}

void t_partEditor2::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPen dotPen;
	painter.setBackgroundMode(Qt::OpaqueMode);
	painter.setBackground(QBrush(QColor(255,255,255)));
	dotPen.setStyle(Qt::DashLine);
	dotPen.setColor(QColor(200,200,200));
	painter.setPen(dotPen);
	painter.fillRect(0,0,2000,2000,QColor(255,255,255));
	for(uint16_t x = 0; x != 2000; x += 50)
	{
		painter.drawLine(x,0,x,2000);
		painter.drawLine(0,x,2000,x);
	}
	dotPen.setColor(QColor(100,100,100));
	painter.setPen(dotPen);
	painter.drawLine(500,490,500,510);
	painter.drawLine(490,500,510,500);
	painter.drawLine(0,0, dotX,dotY);
}

void t_partEditor2::mouseMoveEvent(QMouseEvent *event)
{
	dotX = event->x();
	dotY = event->y();
	repaint();
}
