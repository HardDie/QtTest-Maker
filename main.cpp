#include <QApplication>
#include "uitestmaker.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ucUiTestMaker* w = new ucUiTestMaker();

#if (defined Q_OS_WIN) || (defined Q_OS_LINUX)
	w->show();
#else
	w->showFullScreen();
#endif

	return a.exec();
}
