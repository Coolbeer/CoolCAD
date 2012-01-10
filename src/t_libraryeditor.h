#ifndef T_LIBRARYEDITOR2_H
#define T_LIBRARYEDITOR2_H

#include <QtGui/QWidget>
#include <cstdint>

#include "t_symbol.h"
#include "t_infoWindow.h"

#define SELECT 0
#define MOVE 1
#define LINE 2
#define PIN  4
#define INFO 8

class t_libraryEditor : public QWidget
{
    Q_OBJECT
    public:
                                                    t_libraryEditor(void);
        uint16_t                                    roundNumber(uint16_t number);
        void                                        cancel(void);
        t_library                                   *library;
        t_component                                 *currentComponent;
        bool                                        haveComp;
        QColor                                      g_color, p_color;
    public slots:
        void                                        drawWire(QPoint pos);
        void                                        drawPin(QPoint pos);
        void                                        moveItem(QPoint pos);
        void                                        buttonClicked(QAction *act);
        void                                        openLib(void);
    private:
        void                                        drawGrid(void);
        QLine                                       incompleteLine;
        uint8_t                                     mode;
        double                                      scale;
        t_infoWindow                                *infoWindow;
        bool                                        incompleteStage, pinPlacement, selectPin;
        double                                      hitTest(const QPoint &A, const QPoint &B, const QPoint &C);
        std::vector<t_symbolObject*>::iterator      selected;
    signals:
        void                                        drawWireSignal(QPoint pos);
        void                                        drawPinSignal(QPoint pos);
        void                                        moveItemSignal(QPoint pos);
    protected:
        void                                        paintEvent(QPaintEvent *event);
        void                                        mouseMoveEvent(QMouseEvent *event);
        void                                        mousePressEvent(QMouseEvent *event);
        void                                        wheelEvent (QWheelEvent *event); 

};

#endif
