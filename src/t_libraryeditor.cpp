#include "t_libraryeditor.moc"

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QAction>
#include <QtGui/QFileDialog>
#include <boost/algorithm/string.hpp>
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
    haveComp = false;
    g_color = QColor(200, 100, 100);
    p_color = QColor(100, 200, 100);

    offsetx = 500;
    offsety = 500;
    hintWidth = 4000;
    hintHeight = 4000;

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

QSize t_libraryEditor::sizeHint(void) const
{
    return (QSize(hintWidth, hintHeight));
}

void t_libraryEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush polyBrush;
    polyBrush.setColor(g_color);
    QPen dotPen;
    uint8_t minThickness = 4;
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.scale(scale, scale);
    painter.translate(offsetx,offsety);
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

    if(haveComp)
    {
        for(uint16_t t = 0; t != currentComponent->items.size(); ++t)
        {
            if(currentComponent->items.at(t)->thickness < minThickness)
                currentComponent->items.at(t)->thickness = minThickness;
            if(currentComponent->items.at(t)->type == 'P')
            {
                t_PolylineObject *ob = static_cast<t_PolylineObject*>(currentComponent->items.at(t));
                paintPolygon(painter, *ob);
            }
            else if(currentComponent->items.at(t)->type == 'C')
            {
                t_CircleObject *ob = static_cast<t_CircleObject*>(currentComponent->items.at(t));
                dotPen.setWidth(ob->thickness);
                dotPen.setStyle(Qt::SolidLine);
                dotPen.setColor(g_color);
                painter.setPen(dotPen);
                painter.setBrush(Qt::NoBrush);

                painter.drawEllipse(QPoint(ob->posx, ob->posy), ob->radius, ob->radius);
                //std::cout << ob->posx << "-" << ob->posy << "-" << ob->radius << "\n";
            }
            else if(currentComponent->items.at(t)->type == 'X')
            {
                t_PinObject *ob = static_cast<t_PinObject*>(currentComponent->items.at(t));
                dotPen.setWidth(minThickness);
                dotPen.setStyle(Qt::SolidLine);
                dotPen.setColor(g_color);
                painter.setPen(dotPen);
                painter.setBrush(Qt::NoBrush);
                int16_t tox, toy;
                tox = toy = 0;
                if(ob->direction == 'U')
                {
                    tox = ob->posx;
                    toy = ob->posy - ob->length;
                }
                else if(ob->direction == 'D')
                {
                    tox = ob->posx;
                    toy = ob->posy + ob->length;
                }
                else if(ob->direction == 'R')
                {
                    tox = ob->posx + ob->length;
                    toy = ob->posy;
                }
                else if(ob->direction == 'L')
                {
                    tox = ob->posx - ob->length;
                    toy = ob->posy;
                }
                painter.drawLine(ob->posx, ob->posy, tox, toy);

                dotPen.setColor(p_color);
                dotPen.setWidth(2);
                painter.setPen(dotPen);
                painter.drawEllipse(QPoint(ob->posx, ob->posy), 10, 10);
            }
            else if(currentComponent->items.at(t)->type == 'S')
            {
                //std::cout << "rect\n";
                t_RectangleObject *ob = static_cast<t_RectangleObject*>(currentComponent->items.at(t));
                dotPen.setWidth(ob->thickness);
                dotPen.setStyle(Qt::SolidLine);
                dotPen.setColor(g_color);
                painter.setPen(dotPen);
                painter.drawRect(ob->rect());
//                std::cout << ob->posx << " - " << ob->posy << " - " << ob->endx << " - " << ob->endy << " s\n";
            }
            else if(currentComponent->items.at(t)->type == 'A')
            {
                //std::cout << "arc\n";
                t_ArcObject *ob = static_cast<t_ArcObject*>(currentComponent->items.at(t));
                dotPen.setWidth(ob->thickness);
                dotPen.setStyle(Qt::SolidLine);
                dotPen.setColor(g_color);
                painter.setPen(dotPen);
                painter.drawArc(ob->posx - ob->radius, ob->posy - ob->radius, ob->radius*2, ob->radius*2 , ob->start_angle, ob->end_angle);
            }
        }
        for(uint8_t t = 0; t != currentComponent->fields.size(); ++t)
        {
            t_component_field tF = currentComponent->fields.at(t);
            if(tF.flags & (1 << VISIBLE))
            {
                paintText(painter, tF);
            }
        }
    }

/*    if(incompleteStage)
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
    */
    dotPen.setColor(QColor(100,100,100));
    dotPen.setWidth(1);
    painter.setPen(dotPen);
    painter.drawLine(0,-10,0,10);
    painter.drawLine(-10,0,10,0);
    event->accept();
}

void t_libraryEditor::paintPolygon(QPainter &painter, const t_PolylineObject &ob)
{
//    t_PolylineObject *ob = static_cast<t_PolylineObject*>(currentComponent->items.at(t));
    QPolygon poly;
    for(uint16_t i = 0; i != ob.points.size(); ++i)
    {
        poly << QPoint(ob.points.at(i).x, ob.points.at(i).y);
    }
    QPen dotPen;
    dotPen.setWidth(ob.thickness);
    dotPen.setStyle(Qt::SolidLine);
    dotPen.setColor(g_color);
    painter.setPen(dotPen);
    if(ob.fill == 'F')
    {
        painter.setBrush(QBrush(g_color,Qt::SolidPattern));
        painter.drawPolygon(poly,Qt::WindingFill);
    }
    else
    {
        painter.setBrush(Qt::NoBrush);
        painter.drawPolyline(poly);
    }
}

void t_libraryEditor::paintText(QPainter &painter, t_component_field &tF)
{
    int16_t newX, newY;
    newX = tF.posx;
    newY = tF.posy;

    painter.save();

    QFont tFont;
    tFont.setPixelSize(tF.text_size);
    painter.setFont(tFont);

    QFontMetrics fm(tFont);
    int16_t fmW, fmH;
    fmW = fm.width(QString::fromStdString(tF.name));
    fmH = fm.height();
    
    if(tF.htext_justify == 'C')
        fmW /= 2;
    else if(tF.htext_justify == 'L')
        fmW = 0;
    if(tF.vtext_justify == 'C')
        fmH /= 2;

    if(tF.flags & (1 << TEXT_ORIENT))
    {
        fmH = fmW;
        fmW = 0;
    }
    painter.translate(newX-fmW, newY+fmH);

    if(tF.flags & (1 << TEXT_ORIENT))
        painter.rotate(270);

    QPen dotPen;
    dotPen.setWidth(4);
    dotPen.setStyle(Qt::SolidLine);
    dotPen.setColor(g_color);
    painter.setPen(dotPen);


    painter.setBackground(QBrush(QColor(0,0,0,0)));

    painter.drawText(0, 0, QString::fromStdString(tF.name));
    painter.restore();
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
/*        for(std::vector<t_symbolObject*>::iterator iter = symbol->items.begin(); iter != symbol->items.end(); ++iter)
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
*/
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
//        symbol->addLine(incompleteLine);
        incompleteStage = false;
    }
}

void t_libraryEditor::drawPin(QPoint pos)
{
    pos.setX(roundNumber(pos.x()/scale));
    pos.setY(roundNumber(pos.y()/scale));
//    symbol->addPin(pos);
    
    if(mode == MOVE)
        pinPlacement = false;
}

void t_libraryEditor::moveItem(QPoint pos)
{
    bool selPos = false;
    pos.setX(roundNumber(pos.x()/scale));
    pos.setY(roundNumber(pos.y()/scale));

    std::vector<std::vector<t_symbolObject*>::iterator> closeItems;
/*    for(std::vector<t_symbolObject*>::iterator iter = symbol->items.begin(); iter != symbol->items.end(); ++iter)
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
*/
    if(closeItems.empty())
        return;
    else if(closeItems.size() == 1 || selPos == true)
    {
/*        QLine tmLine = (*closeItems.at(selectedPos))->getData();
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
        */
    }
    else
    {
        selectPin = true;
//        (*closeItems.at(0))->selected = true;
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
    library = new t_library;
    QString fileName = QFileDialog::getOpenFileName(this, "Open Library", "", "Kicad Library (*.lib)");

    library->load(fileName.toStdString());
}

uint16_t t_libraryEditor::roundNumber(uint16_t number)
{
    double tempVal = 50;
    uint16_t returnValue = number / tempVal;
    if(number -returnValue*tempVal >= tempVal/2)
        ++returnValue;
    return returnValue *tempVal;
}

void t_libraryEditor::calculateSizeHint(void)
{
    QRect currentRect;
    for(uint16_t t = 0; t != currentComponent->items.size(); ++t)
    {
        QRect hopp = currentComponent->items.at(t)->rect();
        std::cout << currentComponent->items.at(t)->type << "\n";
        if(!hopp.isNull())
            checkSize(currentRect, hopp);
    }
    for(uint16_t  t = 0; t != currentComponent->fields.size(); ++t)
    {
        QRect hopp = currentComponent->fields.at(t).rect();
        if(!hopp.isNull())
            checkSize(currentRect, hopp);
    }
    hintWidth =  currentRect.width() +100;
    hintHeight = currentRect.height() +100;
    offsetx = -currentRect.left() + 50;
    offsety = -currentRect.top() + 50;
    setGeometry(QRect(this->x(), this->y(), hintWidth, hintHeight));
    std::cout << offsetx << " -- " << offsety << "\n";
    std::cout << hintWidth << " -- " << hintHeight << "\n";
}

void t_libraryEditor::checkSize(QRect &currentRect, QRect &newRect)
{
    if(newRect.left() < currentRect.left())
        currentRect.setLeft(newRect.left());
    if(newRect.right() > currentRect.right())
        currentRect.setRight(newRect.right());
    if(newRect.top() < currentRect.top())
        currentRect.setTop(newRect.top());
    if(newRect.bottom() > currentRect.bottom())
        currentRect.setBottom(newRect.bottom());
}
