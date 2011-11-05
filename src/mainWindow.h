#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMdiSubWindow>
#include <QtGui/QKeyEvent>

#include "parteditor2.h"

class t_mainWindow : public QMainWindow
{
	Q_OBJECT
    public:
                        t_mainWindow();
	public slots:
		void			openPartEditor(void);
    private:
		QAction			*pEditorAction;
		QMdiArea		*mdiArea;
		QMdiSubWindow	*partEditorWindow;
		t_partEditor2	*pEditor;
		void			createMenu(void);
		void			testObject(void);
	protected:
		void			keyPressEvent(QKeyEvent *event);

};

#endif
