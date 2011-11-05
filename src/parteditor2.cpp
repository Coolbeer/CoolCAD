#include "parteditor2.moc"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <cstdint>
#include <iostream>

t_partEditor2::t_partEditor2(void)
{
	setMouseTracking(true);
	mode = NORMAL;
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

	dotPen.setColor(QColor(200,100,100));
	dotPen.setWidth(5);
	dotPen.setStyle(Qt::SolidLine);
	painter.setPen(dotPen);

	if(!partLines.empty())
	{
		for(std::vector<QRect>::iterator iter = partLines.begin(); iter != partLines.end(); ++iter)
			painter.drawLine(iter->x(), iter->y(), iter->width(), iter->height());
	}
	if(mode == LINE)
	{
		painter.drawLine(startDotX, startDotY, dotX, dotY);
	}
}

void t_partEditor2::mouseMoveEvent(QMouseEvent *event)
{
	dotX = roundNumber(event->x());
	dotY = roundNumber(event->y());
	repaint();
}

void t_partEditor2::mousePressEvent(QMouseEvent *event)
{
	if(mode == NORMAL)
	{
		startDotX = roundNumber(event->x());
		startDotY = roundNumber(event->y());
		mode = LINE;
	}
	else if(mode == LINE)
	{
		QRect newRect;
		newRect.setX(startDotX);
		newRect.setY(startDotY);
		newRect.setWidth(roundNumber(event->x()));
		newRect.setHeight(roundNumber(event->y()));
		partLines.push_back(newRect);
		startDotX = 0;
		startDotY = 0;
		mode = NORMAL;
	}
	repaint();
}

void t_partEditor2::cancel(void)
{
	if(mode = LINE)
		mode = NORMAL;
}

uint16_t t_partEditor2::roundNumber(uint16_t number)
{
	uint16_t returnValue = number / 50;
	if(number % 50 >= 25)
		++returnValue;
	return returnValue *50;
}
