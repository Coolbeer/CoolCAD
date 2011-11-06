#include "t_infoWindow.h"

#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <boost/lexical_cast.hpp>

t_infoWindow::t_infoWindow(const t_wireObject &obj)
{
	QLabel *typeLabel	=	new QLabel("Wire");
	QLabel *fromLabel	=	new QLabel("From");
	QLabel *toLabel		=	new QLabel("To");
	QLabel *xLabel		=	new QLabel("x");
	QLabel *x2Label		=	new QLabel("x");
	QLabel *widthLabel	=	new QLabel("Width");

	posEditX			=	new QLineEdit;
	posEditY			=	new QLineEdit;
	pos2EditX			=	new QLineEdit;
	pos2EditY			=	new	QLineEdit;

	QComboBox *widthBox  = new QComboBox;
	for(uint16_t tall = 0; tall != 10; ++tall)
		widthBox->addItem(QString::fromStdString(boost::lexical_cast<std::string>(tall)));

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(typeLabel, 0, 0);
	layout->addWidget(fromLabel, 1, 0);
	layout->addWidget(toLabel, 2, 0);
	layout->addWidget(widthLabel, 3, 0);
	layout->addWidget(widthBox, 3,1);

	layout->addWidget(posEditX, 1, 1);
	layout->addWidget(xLabel, 1, 2);
	layout->addWidget(posEditY, 1, 3);

	layout->addWidget(pos2EditX, 2, 1);
	layout->addWidget(x2Label, 2, 2);
	layout->addWidget(pos2EditY, 2, 3);

	setLayout(layout);
}
