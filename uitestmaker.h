#ifndef TESTMAKER_H
#define TESTMAKER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStackedWidget>
#include <QTextEdit>
#include <QFileDialog>
#include <QListWidget>
#include "testmaker.h"

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

	QLabel          *   outCounter[2];
	QTextEdit       *   outTextQueAns;
	QTextEdit       *   outTextType;
	QListWidget     *   outTextDict;
	QLineEdit       *   inTextType;
	QLineEdit       *   inTextDict[2];

	// Делаем кнопку глобальной, чтобы можно было сделать ее активной по умолчанию
	QPushButton     *   buttonCheck;

	QStackedWidget  *   stackedWidget;

	void                InitAllObjects();

	state_t             currentState;
	test_t              currenteTest;

	void InitMainMenu();
	void InitNextWord();
	void InitTypeAns();
	void InitSetupDict();

private slots:
	void SlotMenu();
	void SlotQueAns();
	void SlotAnsQue();
	void SlotMix();
	void SlotTypeQueAns();
	void SlotTypeAnsQue();
	void SlotTypeMix();
	void SlotNext();
	void SlotDecreaseFont();
	void SlotIncreaseFont();
	void SlotSkipWord();
	void SlotNewFile();
	void SlotManageDict();
	void SlotAddNewQue();
	void SlotDeleteQue();
	void SlotEditQue();
	void SlotSave();
};

#endif // TESTMAKER_H
