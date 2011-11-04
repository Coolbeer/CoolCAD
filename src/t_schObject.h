#ifndef T_SCHOBJECT_H
#define T_SCHOBJECT_H

#include <QtGui/QGraphicsItem>
#include <QtGui/QPainter>
#include <QtGui/QWidget>

class t_schObject : public QWidget, public QGraphicsItem
{
    Q_OBJECT
    public:
		using				QGraphicsItem::show;
                            t_schObject(void);
        QRectF              boundingRect() const;
        void                paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif
