#include "uitestmaker.h"
#include <QApplication>
#include "global.h"
#include "testmaker.h"
#include "testfunctions.h"
#include "testchartranslate.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	ucUiTestMaker* w = new ucUiTestMaker();
	w->show();

	return a.exec();
}
