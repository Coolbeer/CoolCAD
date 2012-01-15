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

class someTextClass;

class t_libraryEditor : public QWidget
{
    Q_OBJECT
    public:
                                                    t_libraryEditor(void);
        uint16_t                                    roundNumber(uint16_t number);
        void                                        cancel(void);
        void                                        calculateSizeHint(void);
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
        QSize                                       sizeHint(void) const;
        void                                        drawGrid(void);
        void                                        paintText(QPainter &painter, const t_component_field &tF);
        void                                        drawText(QPainter &painter, const someTextClass &text);
        void                                        paintPolygon(QPainter &painter, const t_PolylineObject &ob);
        void                                        paintCircle(QPainter &painter, const t_CircleObject &ob);
        void                                        paintPin(QPainter &painter, const t_PinObject &ob);
        void                                        paintRectangle(QPainter &painter, const t_RectangleObject &ob);
        void                                        paintArc(QPainter &painter, const t_ArcObject &ob);
        void                                        checkSize(QRect &currentRect, QRect &newRect);
        int16_t                                     hintWidth, hintHeight;
        int16_t                                     offsetx, offsety;
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

class someTextClass
{
    public:
                                                    someTextClass(void);
        std::string                                 theText;
        int16_t                                     posX, posY;
        uint16_t                                    direction;
        QFont                                       font;
};
#endif
