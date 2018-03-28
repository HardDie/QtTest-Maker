#ifndef TESTMAKER_H
#define TESTMAKER_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTextEdit>
#include "testmaker.h"

#include <QFileDialog>
#include <QDir>
#include <QSysInfo>

enum test_t{
	TEST_QA,
	TEST_AQ,
	TEST_MIX,
	TEST_TYPEQUESTION,
	TEST_TYPEANSWER,
	TEST_TYPEMIX
};

enum state_t{
	STATE_INIT,
	STATE_FIRST_STEP,
	STATE_SECOND_STEP,
	STATE_CHECK_ANSWER
};

class ucUiTestMaker : public QDialog {
	Q_OBJECT

public:
	ucUiTestMaker( QWidget* parent = 0 );
	~ucUiTestMaker();
private:
	uns::ucTestMaker    testInterface;

	QLineEdit       *   lineText;

	QLabel          *   labelFreeLine;
	QLabel          *   labelFreeLine2;
	QLabel          *   outCounter;
	QTextEdit       *   outTextQueAns;

	QStackedWidget  *   stackedWidget;

	void                InitAllObjects();

	state_t             currentState;
	test_t              currenteTest;

private slots:
	void SlotMenu();
	void SlotQueAns();
	void SlotAnsQue();
	void SlotMix();
	void SlotTypeQueAns();
	void SlotTypeAnsQue();
	void SlotTypeMix();
	void SlotNext();
	void SlotNewFile();
};

#endif // TESTMAKER_H
