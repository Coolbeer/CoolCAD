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

	if(!symbol->items.empty())
	{
		for(uint8_t teller = 0;  teller != symbol->items.size(); ++teller)
		{
/*			if(symbol->items.at(teller)->selected)
				dotPen.setColor(QColor(200,10,10));
			else
				dotPen.setColor(QColor(200,100,100));
*/
			if(symbol->items.at(teller)->type == WIRE)
			{
				dotPen.setWidth(5);
				dotPen.setStyle(Qt::SolidLine);
				dotPen.setColor(QColor(200,100,100));
				painter.setPen(dotPen);
				painter.drawLine(symbol->items.at(teller)->getData());
			}
			else if(symbol->items.at(teller)->type == PIN)
			{
				dotPen.setWidth(0);
				dotPen.setColor(QColor(50,200,50));
				painter.setPen(dotPen);
				painter.drawEllipse(symbol->items.at(teller)->getData().p1(), 10, 10);
			}
		}
	}
	if((mode == LINE || mode & EDIT) && startDotX != -10000 && startDotY != -10000)
	{
		dotPen.setWidth(5);
		dotPen.setStyle(Qt::SolidLine);
		dotPen.setColor(QColor(200,100,100));
		painter.setPen(dotPen);
		
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
	std::vector<t_symbolObject*> itemList;
	if(event->button() == Qt::LeftButton)
	{
		std::cout << event->x() << " - " << event->y() << "\n";
		if(mode == MOVE)
		{
/*			int16_t tempX = (-500+roundNumber(translateMouse(event->x())))/50;
			int16_t tempY = (-500+roundNumber(translateMouse(event->y())))/50;
			std::cout << tempX << " = " << tempY << "\n";
			for(uint8_t teller = 0; teller != symbol->items.size(); ++teller)
			{

				if((symbol->items.at(teller).  .line.x1() == tempX && symbol->items.line.y1() == tempY) || (symbol->items.line.x2() == tempX && symbol->items.line.y2() == tempY))
				{
					t_wireObject *test;
					test = static_cast<t_wireObject*>(&symbol->items.at(teller));

					itemList.push_back(*iter);
					if(tempX == iter->line.x1())
					{
						startDotX = iter->line.x2();
						startDotY = iter->line.y2();
					}
					else
					{
						startDotX = iter->line.x1();
						startDotY = iter->line.y1();
					}
					symbol->wires.erase(iter);
					mode |= EDIT;
					break;

				}
				std::cout << itemList.size() << " <--\n";
			}
			*/
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
		else if(mode == PIN)
		{
			QPoint pinPoint((-500+roundNumber(translateMouse(event->x())))/50,(-500+roundNumber(translateMouse(event->y())))/50);
			symbol->addPin(pinPoint);
		}
		else if(mode == INFO)
		{
//			infoWindow = new t_infoWindow(*symbol->pins.begin());
			infoWindow->show();
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
