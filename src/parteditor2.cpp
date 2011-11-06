#include "parteditor2.moc"

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <cstdint>
#include <iostream>

t_partEditor2::t_partEditor2(void)
{
	setMouseTracking(true);
	mode = MOVE;
	scale = 1;
	startDotX = -10000;
	startDotY = -10000;
	symbol = new t_symbol;
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

	if(!symbol->empty())
	{
		for(std::vector<QLine>::iterator iter = symbol->begin(); iter != symbol->end(); ++iter)
		{
			QLine convLine;
			convLine.setPoints(QPoint(500+(iter->x1()*50), 500+(iter->y1()*50)), QPoint(500+(iter->x2()*50), 500+iter->y2()*50));
			painter.drawLine(convLine);
		}
	}
	if((mode == LINE || mode & EDIT) && startDotX != -10000 && startDotY != -10000)
	{
		QLine convLine;
		convLine.setPoints(QPoint(500+(startDotX*50), 500+(startDotY*50)), QPoint(500+(dotX*50), 500+(dotY*50)));
		painter.drawLine(convLine);
	}

	dotPen.setColor(QColor(100,100,100));
	dotPen.setWidth(1);
	painter.setPen(dotPen);
	painter.drawLine(500,490,500,510);
	painter.drawLine(490,500,510,500);
}

void t_partEditor2::mouseMoveEvent(QMouseEvent *event)
{
	dotX = (-500+roundNumber(translateMouse(event->x())))/50;
	dotY = (-500+roundNumber(translateMouse(event->y())))/50;
	repaint();
	event->accept();
}

void t_partEditor2::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		std::cout << event->x() << " - " << event->y() << "\n";
		if(mode == MOVE)
		{
			int16_t tempX = (-500+roundNumber(translateMouse(event->x())))/50;
			int16_t tempY = (-500+roundNumber(translateMouse(event->y())))/50;
			std::cout << tempX << " = " << tempY << "\n";
			for(std::vector<QLine>::iterator iter = symbol->begin(); iter != symbol->end(); ++iter)
			{
				if((iter->x1() == tempX && iter->y1() == tempY) || (iter->x2() == tempX && iter->y2() == tempY))
				{
					if(tempX == iter->x1())
					{
						startDotX = iter->x2();
						startDotY = iter->y2();
					}
					else
					{
						startDotX = iter->x1();
						startDotY = iter->y1();
					}
					symbol->removeLine(iter - symbol->begin());
					mode |= EDIT;
					break;
				}
			}
		}
		else if(mode == LINE)
		{
			if(startDotX == -10000 && startDotY == -10000)
			{
				startDotX = (-500+roundNumber(translateMouse(event->x())))/50;
				startDotY = (-500+roundNumber(translateMouse(event->y())))/50;
				mode |= EDIT;
			}
		}
		else if(mode & EDIT)
		{
			QLine newLine;
			newLine.setLine(startDotX, startDotY, dotX, dotY);
			symbol->addLine(newLine);
			startDotX = -10000;
			startDotY = -10000;
			mode &= ~EDIT;
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

uint16_t t_partEditor2::translateMouse(uint16_t num)
{
	return num/scale;
}

uint16_t t_partEditor2::roundNumber(uint16_t number)
{
	double tempVal = 50;
	uint16_t returnValue = number / tempVal;
	if(number -returnValue*tempVal >= tempVal/2)
		++returnValue;
	return returnValue *tempVal;
}
