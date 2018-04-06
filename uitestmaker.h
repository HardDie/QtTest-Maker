#ifndef TESTMAKER_H
#define TESTMAKER_H

#define VERSION "TestMaker v1.0"

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
#include <QInputDialog>
#include <QDir>
#include "testmaker.h"

enum test_t {
	TEST_QA,
	TEST_AQ,
	TEST_MIX,
	TEST_TYPEQUESTION,
	TEST_TYPEANSWER,
	TEST_TYPEMIX
};

enum state_t {
	STATE_INIT,
	STATE_FIRST_STEP,
	STATE_SECOND_STEP,
	STATE_CHECK_ANSWER
};

enum widget_t {
	WIDGET_MAIN_MENU = 0,
	WIDGET_SHOW_TEST,
	WIDGET_TYPE_TEST,
	WIDGET_DICT_MANAGE,
	WIDGET_OPEN_FILE
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
	QListWidget     *   outFileList;
	QLineEdit       *   inTextType;
	QLineEdit       *   inTextDict[2];
	QString             pathToDict;

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
	void InitOpenNewFile();

private slots:
	void SlotQueAns();
	void SlotAnsQue();
	void SlotMix();

	void SlotTypeQueAns();
	void SlotTypeAnsQue();
	void SlotTypeMix();

	void SlotNext();
	void SlotMenu();
	void SlotDecreaseFont();
	void SlotIncreaseFont();
	void SlotSkipWord();

	void SlotOpenNewFile();
	void SlotDeleteFile();
	void SlotCreateFile();

	void SlotManageDict();
	void SlotAddNewQuestion();
	void SlotDeleteQuestion();
	void SlotEditQuestion();
	void SlotSaveDictionary();
};

#endif // TESTMAKER_H
