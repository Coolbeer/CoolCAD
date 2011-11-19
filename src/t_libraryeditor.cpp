#include "t_libraryeditor.moc"

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QAction>
#include <QTGui/QFileDialog>
#include <cstdint>
#include <iostream>
#include <math.h>

#include "pwanmath.h"

t_libraryEditor::t_libraryEditor(void)
{
    setMouseTracking(true);
    mode = MOVE;
    scale = 1;
    incompleteStage = false;
    pinPlacement = false;
    symbol = new t_symbol;
    selected = symbol->items.end();

    connect(this, SIGNAL(drawWireSignal(QPoint)), this, SLOT(drawWire(QPoint)));
    connect(this, SIGNAL(drawPinSignal(QPoint)), this, SLOT(drawPin(QPoint)));
    connect(this, SIGNAL(moveItemSignal(QPoint)), this, SLOT(moveItem(QPoint)));
}

void t_libraryEditor::buttonClicked(QAction *act)
{
    if(act->text() == "Move")
        mode = MOVE;
    else if(act->text() == "Draw Line")
        mode = LINE;
    else if(act->text() == "Draw a Pin")
        mode = PIN;
    else if(act->text() == "Info")
        mode = INFO;

    if(mode == PIN)
        pinPlacement = true;
    else
        pinPlacement = false;
    incompleteStage = false;
}

void t_libraryEditor::paintEvent(QPaintEvent *event)
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
            if(symbol->items.at(teller)->type == WIRE)
            {
                dotPen.setWidth(5);
                dotPen.setStyle(Qt::SolidLine);
                if(symbol->items.at(teller)->selected)
                    dotPen.setColor(QColor(250,0,0));
                else
                    dotPen.setColor(QColor(200,100,100));
                painter.setPen(dotPen);
                painter.drawLine(symbol->items.at(teller)->getData());
            }
            else if(symbol->items.at(teller)->type == PIN)
            {
                dotPen.setWidth(1);
                if(symbol->items.at(teller)->selected)
                    dotPen.setColor(QColor(10,200,10));
                else
                    dotPen.setColor(QColor(100,200,100));
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
    else if(pinPlacement)
    {
        dotPen.setWidth(1);
        dotPen.setColor(QColor(100,200,100));
        painter.setPen(dotPen);
        painter.drawEllipse(incompleteLine.p2(), 10, 10);
    }

    dotPen.setColor(QColor(100,100,100));
    dotPen.setWidth(1);
    painter.setPen(dotPen);
    painter.drawLine(500,490,500,510);
    painter.drawLine(490,500,510,500);
}

void t_libraryEditor::mouseMoveEvent(QMouseEvent *event)
{
    incompleteLine.setP2(QPoint(roundNumber(event->x()/scale), roundNumber(event->y()/scale)));
    repaint();
    event->accept();
}

void t_libraryEditor::mousePressEvent(QMouseEvent *event)
{
//  std::vector<t_symbolObject*> itemList;
    if(event->button() == Qt::LeftButton)
    {
        std::cout << event->x() << " - " << event->y() << "\n";
        if(mode == MOVE)
        {
            if(incompleteStage)
                emit drawWireSignal(event->pos());
            else if(pinPlacement)
                emit drawPinSignal(event->pos());
            else 
                emit moveItemSignal(event->pos());
        }
        else if(mode == LINE)
            emit drawWireSignal(event->pos());
        else if(mode == PIN)
            emit drawPinSignal(event->pos());
        else if(mode == INFO)
        {
//          infoWindow = new t_infoWindow(*symbol->pins.begin());
//          infoWindow->show();
        }

    }
    else if(event->button() == Qt::RightButton)
    {
        for(std::vector<t_symbolObject*>::iterator iter = symbol->items.begin(); iter != symbol->items.end(); ++iter)
        {
            if((*iter)->selected)
            {
                (*iter)->selected = false;
                if(iter+1 != symbol->items.end())
                {
                    (*(++iter))->selected = true;
                    break;
                }
                else
                {
                    symbol->items.at(0)->selected = true;
                    break;
                }
            }
        }
    }
    event->accept();
    repaint();
}

double t_libraryEditor::hitTest(const QPoint &A, const QPoint &B, const QPoint &C)
{
    std::vector<uint32_t> vA, vB, vC;
    vA.push_back(A.x());
    vA.push_back(A.y());

    vB.push_back(B.x());
    vB.push_back(B.y());

    vC.push_back(C.x());
    vC.push_back(C.y());

    double dist = pwan::math::cross(vA, vB, vC) / pwan::math::distance(vA, vB);

    int dot1 = pwan::math::dot(vA, vB, vC);
    if(dot1 > 0)
        return pwan::math::distance(vB, vC);
    int dot2 = pwan::math::dot(vB, vA, vC);
    if(dot2 > 0)
        return pwan::math::distance(vA, vC);
    return abs(dist);
}

void t_libraryEditor::drawWire(QPoint pos)
{
    pos.setX(roundNumber(pos.x()/scale));
    pos.setY(roundNumber(pos.y()/scale));

    if(!incompleteStage)
    {
        incompleteLine.setP1(pos);
        incompleteStage = true;
    }
    else if(incompleteStage)
    {
        incompleteLine.setP2(pos);
        symbol->addLine(incompleteLine);
        incompleteStage = false;
    }
}

void t_libraryEditor::drawPin(QPoint pos)
{
    pos.setX(roundNumber(pos.x()/scale));
    pos.setY(roundNumber(pos.y()/scale));
    symbol->addPin(pos);
    
    if(mode == MOVE)
        pinPlacement = false;
}

void t_libraryEditor::moveItem(QPoint pos)
{
    uint8_t selectedPos = 0;
    bool selPos = false;
    pos.setX(roundNumber(pos.x()/scale));
    pos.setY(roundNumber(pos.y()/scale));

    std::vector<std::vector<t_symbolObject*>::iterator> closeItems;
    for(std::vector<t_symbolObject*>::iterator iter = symbol->items.begin(); iter != symbol->items.end(); ++iter)
    {
        QLine tmpLine = (*iter)->getData();
        if((*iter)->type == WIRE)
        {
            if(hitTest(tmpLine.p1(), tmpLine.p2(), pos) < 35)
            {
                closeItems.push_back(iter);
                if((*iter)->selected)
                {
                    selPos = true;
                    selectedPos = closeItems.size()-1;
                }
            }
        }
        else if((*iter)->type == PIN)
        {
            if(pos == tmpLine.p1())
            {
                closeItems.push_back(iter);
                if((*iter)->selected)
                {
                    selPos = true;
                    selectedPos = closeItems.size()-1;
                }
            }
        }
    }

    if(closeItems.empty())
        return;
    else if(closeItems.size() == 1 || selPos == true)
    {
        QLine tmLine = (*closeItems.at(selectedPos))->getData();
        if((*closeItems.at(selectedPos))->type == WIRE)
        {
            if(tmLine.p1() == pos)
            {
                incompleteLine.setP1(tmLine.p2());;
                incompleteStage = true;
                symbol->items.erase(closeItems.at(selectedPos));
            }
            else if(tmLine.p2() == pos)
            {
                incompleteLine.setP1(tmLine.p1());;
                incompleteStage = true;
                symbol->items.erase(closeItems.at(selectedPos));
            }
        }
        else if((*closeItems.at(0))->type == PIN)
        {
            if(tmLine.p1() == pos)
            {
                pinPlacement = true;
                symbol->items.erase(closeItems.at(selectedPos));
            }
        }
    }
    else
    {
        selectPin = true;
        (*closeItems.at(0))->selected = true;
    }
}

void t_libraryEditor::cancel(void)
{
}

void t_libraryEditor::wheelEvent(QWheelEvent *event)
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

void t_libraryEditor::openLib(void)
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Library", "", "Kicad Library (*.lib)");
    std::cout << fileName.toStdString() << "\n";
}

uint16_t t_libraryEditor::roundNumber(uint16_t number)
{
    double tempVal = 50;
    uint16_t returnValue = number / tempVal;
    if(number -returnValue*tempVal >= tempVal/2)
        ++returnValue;
    return returnValue *tempVal;
}
