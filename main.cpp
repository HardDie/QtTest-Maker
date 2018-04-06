#include <QApplication>
#include "uitestmaker.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ucUiTestMaker* w = new ucUiTestMaker();

#if defined Q_OS_ANDROID
	w->showFullScreen();
#else
	w->show();
#endif

	return a.exec();
}
