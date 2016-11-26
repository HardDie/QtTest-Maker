#include "uitestmaker.h"
#include <QApplication>
#include "global.h"
#include "testmaker.h"
#include "testfunctions.h"
#include "testchartranslate.h"

#include <QSysInfo>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ucUiTestMaker* w = new ucUiTestMaker();

#ifdef Q_OS_WIN
    w->show();
#else
    w->showFullScreen();
#endif

	return a.exec();
}
