#ifndef T_INFOWINDOW_H
#define T_INFOWINDOW_H

#include "t_symbol.h"

#include <QtGui/QWidget>
#include <QtGui/QLineEdit>

class t_infoWindow : public QWidget
{
    public:
        t_infoWindow(const t_wireObject &obj);
        t_infoWindow(const t_pinObject &obj);
    private:
        QLineEdit *nameEdit;
        QLineEdit *posEditX;
        QLineEdit *posEditY;
        QLineEdit *pos2EditX;
        QLineEdit *pos2EditY;
};

#endif
