#include "t_schObject.h"
#include "t_schObject.moc"

#include <iostream>

t_schObject::t_schObject(void)
{

}

void t_schObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen qp;
    qp.setColor(QColor(0,0,0));
    qp.setWidth(2);
    painter->setPen(qp);
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
    painter->drawText(0,0,"Hepp");
}

QRectF t_schObject::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-100 - penWidth / 2, -100 - penWidth / 2,
                  200 + penWidth, 200 + penWidth);
}
