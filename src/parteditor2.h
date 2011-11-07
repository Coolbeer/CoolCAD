#ifndef PARTEDITOR2_H
#define PARTEDITOR2_H

#include <QtGui/QWidget>
#include <cstdint>

#include "t_symbol.h"
#include "t_infoWindow.h"

#define MOVE 1
#define LINE 2
#define PIN  4
#define INFO 8

class t_partEditor2 : public QWidget
{
    Q_OBJECT
    public:
                            t_partEditor2(void);
        uint16_t            roundNumber(uint16_t number);
        void                cancel(void);
        void                setToolBarButton(uint8_t number);
    public slots:
        void                drawWire(QPoint pos);
        void                drawPin(QPoint pos);
        void                moveItem(QPoint pos);
    private:
        void                drawGrid(void);
        QLine               incompleteLine;
        uint8_t             mode;
        double              scale;
        t_symbol            *symbol;
        t_infoWindow        *infoWindow;
        bool                incompleteStage, pinPlacement;
    signals:
        void                drawWireSignal(QPoint pos);
        void                drawPinSignal(QPoint pos);
        void                moveItemSignal(QPoint pos);
    protected:
        void                paintEvent(QPaintEvent *event);
        void                mouseMoveEvent(QMouseEvent *event);
        void                mousePressEvent(QMouseEvent *event);
        void                wheelEvent (QWheelEvent *event); 
};

#endif
