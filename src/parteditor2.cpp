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
	incompleteStage = false;
	symbol = new t_symbol;
	connect(this, SIGNAL(drawWireSignal(QPoint)), this, SLOT(drawWire(QPoint)));
	connect(this, SIGNAL(drawPinSignal(QPoint)), this, SLOT(drawPin(QPoint)));
	connect(this, SIGNAL(moveItemSignal(QPoint)), this, SLOT(moveItem(QPoint)));
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
	if(incompleteStage)
	{
		dotPen.setWidth(5);
		dotPen.setStyle(Qt::SolidLine);
		dotPen.setColor(QColor(200,100,100));
		painter.setPen(dotPen);
		painter.drawLine(incompleteLine);
	}

	dotPen.setColor(QColor(100,100,100));
	dotPen.setWidth(1);
	painter.setPen(dotPen);
	painter.drawLine(500,490,500,510);
	painter.drawLine(490,500,510,500);
}

void t_partEditor2::mouseMoveEvent(QMouseEvent *event)
{
	incompleteLine.setP2(QPoint(roundNumber(event->x()/scale), roundNumber(event->y()/scale)));
	repaint();
	event->accept();
}

void t_partEditor2::mousePressEvent(QMouseEvent *event)
{
//	std::vector<t_symbolObject*> itemList;
	if(event->button() == Qt::LeftButton)
	{
		std::cout << event->x() << " - " << event->y() << "\n";
		if(mode == MOVE)
		{
			if(incompleteStage)
				emit drawWireSignal(event->pos());
			else
				emit moveItemSignal(event->pos());
		}
		else if(mode == LINE)
			emit drawWireSignal(event->pos());
		else if(mode == PIN)
			emit drawPinSignal(event->pos());
		else if(mode == INFO)
		{
//			infoWindow = new t_infoWindow(*symbol->pins.begin());
//			infoWindow->show();
		}
	}
	event->accept();
	repaint();
}

void t_partEditor2::drawWire(QPoint pos)
{
	pos.setX(roundNumber(pos.x()/scale));
	pos.setY(roundNumber(pos.y()/scale));

	if(incompleteStage == false)
	{
		incompleteLine.setP1(pos);
		incompleteStage = true;;
	}
	else if(incompleteStage == true)
	{
		incompleteLine.setP2(pos);
		symbol->addLine(incompleteLine);
		incompleteStage = false;
	}
}

void t_partEditor2::drawPin(QPoint pos)
{
	pos.setX(roundNumber(pos.x()/scale));
	pos.setY(roundNumber(pos.y()/scale));
	symbol->addPin(pos);
}

void t_partEditor2::moveItem(QPoint pos)
{
	pos.setX(roundNumber(pos.x()/scale));
	pos.setY(roundNumber(pos.y()/scale));

	for(std::vector<t_symbolObject*>::iterator iter = symbol->items.begin(); iter != symbol->items.end(); ++iter)
	{
		QLine tmpLine = (*iter)->getData();
		if((*iter)->type == WIRE)
		{
			if(tmpLine.p1() == pos)
			{
				incompleteLine.setP1(tmpLine.p2());;
				incompleteStage = true;
				symbol->items.erase(iter);
				break;
			}
			else if(tmpLine.p2() == pos)
			{
				incompleteLine.setP1(tmpLine.p1());;
				incompleteStage = true;
				symbol->items.erase(iter);
				break;
			}
		}
		else if((*iter)->type == PIN)
		{

		}
	}
}

void t_partEditor2::cancel(void)
{
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
	double tempVal = 50;
	uint16_t returnValue = number / tempVal;
	if(number -returnValue*tempVal >= tempVal/2)
		++returnValue;
	return returnValue *tempVal;
}
