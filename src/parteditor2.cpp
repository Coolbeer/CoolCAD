#include "parteditor2.moc"
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <cstdint>
#include <iostream>

t_partEditor2::t_partEditor2(void)
{
	setMouseTracking(true);
	mode = MOVE;
	scale = 0.5;
	startDotX = 0;
	startDotY = 0;
}

void t_partEditor2::drawGrid(void)
{

}

void t_partEditor2::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPen dotPen;
	painter.scale(scale, scale);
	painter.setBackgroundMode(Qt::OpaqueMode);
	painter.setBackground(QBrush(QColor(255,255,255)));
	painter.fillRect(-2000,-2000,4000,4000,QColor(255,255,255));

	dotPen.setStyle(Qt::DashLine);
	dotPen.setColor(QColor(200,200,200));
	dotPen.setWidth(0);
	painter.setPen(dotPen);
	for(int16_t x = -2000; x != 2000; x += 50)
	{
		painter.drawLine(x,-2000,x,2000);
		painter.drawLine(-2000,x,2000,x);
	}

	dotPen.setColor(QColor(200,100,100));
	dotPen.setWidth(5);
	dotPen.setStyle(Qt::SolidLine);
	painter.setPen(dotPen);

	if(!partLines.empty())
	{
		for(std::vector<QRect>::iterator iter = partLines.begin(); iter != partLines.end(); ++iter)
			painter.drawLine(iter->x(), iter->y(), iter->width(), iter->height());
	}
	if(mode == LINE && startDotX != 0 && startDotY != 0)
	{
		painter.drawLine(startDotX, startDotY, dotX, dotY);
	}

	dotPen.setColor(QColor(100,100,100));
	dotPen.setWidth(1);
	painter.setPen(dotPen);
	painter.drawLine(500,490,500,510);
	painter.drawLine(490,500,510,500);
}

void t_partEditor2::mouseMoveEvent(QMouseEvent *event)
{
	dotX = roundNumber(event->x())/scale;
	dotY = roundNumber(event->y())/scale;
	repaint();
	event->accept();
}

void t_partEditor2::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		if(mode == MOVE)
		{
		}
		else if(mode == LINE)
		{
			if(startDotX == 0 && startDotY == 0)
			{
				startDotX = roundNumber(event->x())/scale;
				startDotY = roundNumber(event->y())/scale;
			}
			else
			{
				QRect newRect;
				newRect.setX(startDotX);
				newRect.setY(startDotY);
				newRect.setWidth(roundNumber(event->x())/scale);
				newRect.setHeight(roundNumber(event->y())/scale);
				partLines.push_back(newRect);
				startDotX = 0;
				startDotY = 0;
			}
		}
	}
	event->accept();
	repaint();
}

void t_partEditor2::cancel(void)
{
	if(mode == LINE)
	{
		startDotX = 0;
		startDotY = 0;
	}
}

void t_partEditor2::wheelEvent(QWheelEvent *event)
{
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;
	std::cout << numSteps << "\n";
	if (event->orientation() == Qt::Vertical)
	{
		if((event->delta() > 0) && scale < 3)
			scale += 0.01;
		else if((event->delta() < 0) && scale >0.1)
			scale -= 0.01;
	}
	std::cout << scale << "\n";
	event->accept();
	repaint();
}

void t_partEditor2::setToolBarButton(uint8_t number)
{
	mode = number;
}

uint16_t t_partEditor2::roundNumber(uint16_t number)
{
	double tempVal = 50*scale;
	uint16_t returnValue = number / tempVal;
	if(number -returnValue*tempVal >= tempVal/2)
		++returnValue;
	return returnValue *tempVal;
}
