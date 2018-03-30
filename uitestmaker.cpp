#include "uitestmaker.h"
#include <QDebug>

ucUiTestMaker::ucUiTestMaker( QWidget* parent ) : QDialog( parent ) {
	setWindowTitle( "TestMaker" );

	// Инициализация сторки номера вопроса
	outCounter[0]    =  new QLabel;
	outCounter[1]    =  new QLabel;
	// Инициализация окон вывода вопроса
	outTextQueAns    =  new QTextEdit;
	outTextType      =  new QTextEdit;
	outTextDict      =  new QListWidget;
	// Инициализация линии ввода ответа
	inTextType       =  new QLineEdit;
	inTextDict[0]    =  new QLineEdit;
	inTextDict[1]    =  new QLineEdit;
	// Окно для слоя Que->Ans
	outTextQueAns->setReadOnly( true );
	outTextQueAns->setFontPointSize( 15 );
	// Окно для слоя Type Ans
	outTextType->setReadOnly( true );
	outTextType->setFontPointSize( 15 );

	SlotNewFile();
	InitAllObjects();
	currentState = STATE_INIT;
}

ucUiTestMaker::~ucUiTestMaker() {

}

/*
====================
InitAllObjects

	Инициализация всех обьектов, создание виджетов, привязка сигналов к слотам
====================
*/
void ucUiTestMaker::InitAllObjects() {
	QPushButton  *  buttonQueAns;
	QPushButton  *  buttonAnsQue;
	QPushButton  *  buttonMix;
	QPushButton  *  buttonTypeQueAns;
	QPushButton  *  buttonTypeAnsQue;
	QPushButton  *  buttonTypeMix;
	QPushButton  *  buttonNewFile;
	QPushButton  *  buttonExit;
	QPushButton  *  buttonNext;
	QPushButton  *  buttonMainMenu[3];
	QPushButton  *  buttonFontIncrease[2];
	QPushButton  *  buttonFontDecrease[2];
	QPushButton  *  buttonSkip;
	QPushButton  *  buttonManageDict;
	QLabel       *  labelFreeLine[4];

	// Инициализация кнопок
	buttonQueAns       = new QPushButton( "Question -> Answer" );
	buttonAnsQue       = new QPushButton( "Answer -> Question" );
	buttonMix          = new QPushButton( "Mix" );
	buttonTypeQueAns   = new QPushButton( "Type Question -> Answer" );
	buttonTypeAnsQue   = new QPushButton( "Type Answer -> Question" );
	buttonTypeMix      = new QPushButton( "Type mix" );
	buttonNewFile      = new QPushButton( "Open new file" );
	buttonExit         = new QPushButton( "Exit" );
	buttonNext         = new QPushButton( "Next" );
	buttonMainMenu[0]  = new QPushButton( "Main menu" );
	buttonMainMenu[1]  = new QPushButton( "Main menu" );
	buttonMainMenu[2]  = new QPushButton( "Main menu" );
	buttonCheck        = new QPushButton( "Check" );
	buttonSkip         = new QPushButton( "Skip" );
	buttonFontDecrease[0] = new QPushButton( "-" );
	buttonFontIncrease[0] = new QPushButton( "+" );
	buttonFontDecrease[1] = new QPushButton( "-" );
	buttonFontIncrease[1] = new QPushButton( "+" );
	buttonManageDict   = new QPushButton( "Manage dictionary" );

	// Инициализация слоя главного меню
	QWidget* widgetMainMenu = new QWidget;
	QVBoxLayout* layoutMainMenu = new QVBoxLayout;
	labelFreeLine[0] = new QLabel( "" );
	layoutMainMenu->addWidget( buttonQueAns );
	layoutMainMenu->addWidget( buttonAnsQue );
	layoutMainMenu->addWidget( buttonMix );
		layoutMainMenu->addWidget( labelFreeLine[0] );
	layoutMainMenu->addWidget( buttonTypeQueAns );
	layoutMainMenu->addWidget( buttonTypeAnsQue );
	layoutMainMenu->addWidget( buttonTypeMix );
		layoutMainMenu->addWidget( labelFreeLine[0] );
	layoutMainMenu->addWidget( buttonManageDict );
	layoutMainMenu->addWidget( buttonNewFile );
	layoutMainMenu->addWidget( buttonExit );
		layoutMainMenu->addWidget( labelFreeLine[0] );
	widgetMainMenu->setLayout( layoutMainMenu );

	// Инициализация слоя для теста по типу следующее слово
	QWidget* widgetNextWord = new QWidget;
	QVBoxLayout* layoutNextWord = new QVBoxLayout;
	labelFreeLine[1] = new QLabel( "" );
	layoutNextWord->addWidget( outCounter[0] );
		layoutNextWord->addWidget( labelFreeLine[1] );
	layoutNextWord->addWidget( outTextQueAns );
		layoutNextWord->addWidget( labelFreeLine[1] );
	layoutNextWord->addWidget( buttonNext );
	layoutNextWord->addWidget( buttonMainMenu[0] );
	QHBoxLayout* layoutFontSize[2];
	layoutFontSize[0] = new QHBoxLayout;
	layoutFontSize[0]->addWidget( buttonFontDecrease[0] );
	layoutFontSize[0]->addWidget( buttonFontIncrease[0] );
	layoutNextWord->addLayout( layoutFontSize[0] );
		layoutNextWord->addWidget( labelFreeLine[1] );
	widgetNextWord->setLayout( layoutNextWord );

	// Инциализация слоя для теста по типу ввод ответа на вопрос
	QWidget* widgetTypeAnswer = new QWidget;
	QVBoxLayout* layoutTypeAnswer = new QVBoxLayout;
	labelFreeLine[2] = new QLabel( "" );
	layoutTypeAnswer->addWidget( outCounter[1] );
		layoutTypeAnswer->addWidget( labelFreeLine[2] );
	layoutTypeAnswer->addWidget( outTextType );
		layoutTypeAnswer->addWidget( labelFreeLine[2] );
	layoutTypeAnswer->addWidget( inTextType );
		layoutTypeAnswer->addWidget( labelFreeLine[2] );
	layoutTypeAnswer->addWidget( buttonCheck );
	layoutTypeAnswer->addWidget( buttonSkip );
	layoutTypeAnswer->addWidget( buttonMainMenu[1] );
	layoutFontSize[1] = new QHBoxLayout;
	layoutFontSize[1]->addWidget( buttonFontDecrease[1] );
	layoutFontSize[1]->addWidget( buttonFontIncrease[1] );
	layoutTypeAnswer->addLayout( layoutFontSize[1] );
		layoutTypeAnswer->addWidget( labelFreeLine[2] );
	widgetTypeAnswer->setLayout( layoutTypeAnswer );

	// Инциализация слоя для управления словарем
	QWidget* widgetManageDict = new QWidget;
	QVBoxLayout* layoutManageDict = new QVBoxLayout;
	labelFreeLine[3] = new QLabel( "" );
	layoutManageDict->addWidget( outTextDict );
		layoutManageDict->addWidget( labelFreeLine[3] );
	QLabel* lableAns = new QLabel( " - " );
	QHBoxLayout* layoutQue = new QHBoxLayout;
	layoutQue->addWidget( inTextDict[0] );
	layoutQue->addWidget( lableAns );
	layoutQue->addWidget( inTextDict[1] );
	layoutManageDict->addLayout( layoutQue );
		layoutManageDict->addWidget( labelFreeLine[3] );
	layoutManageDict->addWidget( buttonMainMenu[2] );
	widgetManageDict->setLayout( layoutManageDict );

	// Подключаем сигналы
	connect( buttonQueAns,          SIGNAL( clicked( bool ) ), this, SLOT( SlotQueAns() ) );
	connect( buttonAnsQue,          SIGNAL( clicked( bool ) ), this, SLOT( SlotAnsQue() ) );
	connect( buttonMix,             SIGNAL( clicked( bool ) ), this, SLOT( SlotMix() ) );
	connect( buttonTypeQueAns,      SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeQueAns() ) );
	connect( buttonTypeAnsQue,      SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeAnsQue() ) );
	connect( buttonTypeMix,         SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeMix() ) );
	connect( buttonNext,            SIGNAL( clicked( bool ) ), this, SLOT( SlotNext() ) );
	connect( buttonCheck,           SIGNAL( clicked( bool ) ), this, SLOT( SlotNext() ) );
	connect( buttonFontIncrease[0], SIGNAL( clicked( bool ) ), this, SLOT( SlotIncreaseFont() ) );
	connect( buttonFontDecrease[0], SIGNAL( clicked( bool ) ), this, SLOT( SlotDecreaseFont() ) );
	connect( buttonMainMenu[0],     SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );
	connect( buttonFontIncrease[1], SIGNAL( clicked( bool ) ), this, SLOT( SlotIncreaseFont() ) );
	connect( buttonFontDecrease[1], SIGNAL( clicked( bool ) ), this, SLOT( SlotDecreaseFont() ) );
	connect( buttonSkip,            SIGNAL( clicked( bool ) ), this, SLOT( SlotSkipWord() ) );
	connect( buttonMainMenu[1],     SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );
	connect( buttonMainMenu[2],     SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );
	connect( buttonManageDict,      SIGNAL( clicked( bool ) ), this, SLOT( SlotManageDict() ) );
	connect( buttonNewFile,         SIGNAL( clicked( bool ) ), this, SLOT( SlotNewFile() ) );
	connect( buttonExit,            SIGNAL( clicked( bool ) ), this, SLOT( close() ) );

	// Инициализируем стэк виджетов
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget( widgetMainMenu );
	stackedWidget->addWidget( widgetNextWord );
	stackedWidget->addWidget( widgetTypeAnswer );
	stackedWidget->addWidget( widgetManageDict );

	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addWidget( stackedWidget );
	setLayout( layoutMain );
}

static void ChangeFontSize(QTextEdit *textEdit, int diff) {
	qreal size = textEdit->fontPointSize();
	size += diff;
	if ( size <= 10 ) size = 10;
	if ( size > 50 ) size = 50;
	textEdit->setFontPointSize( size );
	// Сделано, для обновления текста в окне после изменения шрифта
	QString tmp = textEdit->toPlainText();
	textEdit->setText( tmp );
}

void ucUiTestMaker::SlotDecreaseFont() {
	ChangeFontSize(outTextQueAns, -5);
	ChangeFontSize(outTextType, -5);
}

void ucUiTestMaker::SlotIncreaseFont() {
	ChangeFontSize(outTextQueAns, 5);
	ChangeFontSize(outTextType, 5);
}

void ucUiTestMaker::SlotSkipWord() {
	currentState = STATE_FIRST_STEP;
	SlotNext();
}

void ucUiTestMaker::SlotMenu() {
	stackedWidget->setCurrentIndex( 0 );
	currentState = STATE_INIT;
}

void ucUiTestMaker::SlotQueAns() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( 1 );
		testInterface.Init();
		currentState = STATE_FIRST_STEP;
		currenteTest = TEST_QA;
		SlotNext();
		break;
	case STATE_FIRST_STEP:
		if ( testInterface.NewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() );
		( outCounter[0] )->setText( tmpStringForOutput );
		outTextQueAns->setText( testInterface.GetQuestion() );
		currentState = STATE_SECOND_STEP;
		break;
	case STATE_SECOND_STEP:
		tmpStringForOutput.sprintf( "%s - %s", testInterface.GetQuestion(), testInterface.GetAnswer() );
		outTextQueAns->setText( tmpStringForOutput );
		currentState = STATE_FIRST_STEP;
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotAnsQue() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( 1 );
		testInterface.Init();
		currentState = STATE_FIRST_STEP;
		currenteTest = TEST_AQ;
		SlotNext();
		break;
	case STATE_FIRST_STEP:
		if ( testInterface.NewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() );
		( outCounter[0] )->setText( tmpStringForOutput );
		outTextQueAns->setText( testInterface.GetAnswer() );
		currentState = STATE_SECOND_STEP;
		break;
	case STATE_SECOND_STEP:
		tmpStringForOutput.sprintf( "%s - %s", testInterface.GetAnswer(), testInterface.GetQuestion() );
		outTextQueAns->setText( tmpStringForOutput );
		currentState = STATE_FIRST_STEP;
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotMix() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( 1 );
		testInterface.Init();
		currentState = STATE_FIRST_STEP;
		currenteTest = TEST_MIX;
		SlotNext();
		break;
	case STATE_FIRST_STEP:
		if ( testInterface.MixNewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() * 2 );
		( outCounter[0] )->setText( tmpStringForOutput );
		switch( testInterface.GetFlag() ) {
		case 1:
		case 4:
			outTextQueAns->setText( testInterface.GetAnswer() );
			break;
		case 2:
		case 3:
			outTextQueAns->setText( testInterface.GetQuestion() );
			break;
		}
		currentState = STATE_SECOND_STEP;
		break;
	case STATE_SECOND_STEP:
		switch( testInterface.GetFlag() ) {
		case 1:
		case 4:
			tmpStringForOutput.sprintf( "%s - %s", testInterface.GetAnswer(), testInterface.GetQuestion() );
			break;
		case 2:
		case 3:
			tmpStringForOutput.sprintf( "%s - %s", testInterface.GetQuestion(), testInterface.GetAnswer() );
			break;
		}
		outTextQueAns->setText( tmpStringForOutput );
		currentState = STATE_FIRST_STEP;
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotTypeQueAns() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( 2 );
		testInterface.Init();
		currentState = STATE_FIRST_STEP;
		currenteTest = TEST_TYPEQUESTION;
		buttonCheck->setDefault(true);
		SlotNext();
		break;
	case STATE_FIRST_STEP:
		if ( testInterface.NewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() );
		( outCounter[1] )->setText( tmpStringForOutput );
		outTextType->setText( testInterface.GetQuestion() );
		currentState = STATE_SECOND_STEP;
		break;
	case STATE_SECOND_STEP:
		if (inTextType->text().toLower() ==
		    QString(testInterface.GetAnswer()).toLower()) {
			currentState = STATE_FIRST_STEP;
			inTextType->setText("");
			SlotTypeQueAns();
		} else {
			tmpStringForOutput.sprintf( "%s - %s", testInterface.GetQuestion(), testInterface.GetAnswer() );
			outTextType->setText( tmpStringForOutput );
			inTextType->setText("");
		}
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotTypeAnsQue() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( 2 );
		testInterface.Init();
		currentState = STATE_FIRST_STEP;
		currenteTest = TEST_TYPEANSWER;
		buttonCheck->setDefault(true);
		SlotNext();
		break;
	case STATE_FIRST_STEP:
		if ( testInterface.NewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() );
		( outCounter[1] )->setText( tmpStringForOutput );
		outTextType->setText( testInterface.GetAnswer() );
		currentState = STATE_SECOND_STEP;
		break;
	case STATE_SECOND_STEP:
		if (inTextType->text().toLower() ==
		    QString(testInterface.GetQuestion()).toLower()) {
			currentState = STATE_FIRST_STEP;
			inTextType->setText("");
			SlotTypeAnsQue();
		} else {
			tmpStringForOutput.sprintf( "%s - %s", testInterface.GetAnswer(), testInterface.GetQuestion() );
			outTextType->setText( tmpStringForOutput );
			inTextType->setText("");
		}
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotTypeMix() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( 2 );
		testInterface.Init();
		currentState = STATE_FIRST_STEP;
		currenteTest = TEST_TYPEMIX;
		buttonCheck->setDefault(true);
		SlotNext();
		break;
	case STATE_FIRST_STEP:
		if ( testInterface.MixNewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() * 2 );
		( outCounter[1] )->setText( tmpStringForOutput );
		switch( testInterface.GetFlag() ) {
		case 1:
		case 4:
			outTextType->setText( testInterface.GetAnswer() );
			break;
		case 2:
		case 3:
			outTextType->setText( testInterface.GetQuestion() );
			break;
		}
		currentState = STATE_SECOND_STEP;
		break;
	case STATE_SECOND_STEP:
		switch( testInterface.GetFlag() ) {
		case 1:
		case 4:
			if (inTextType->text().toLower() ==
			    QString(testInterface.GetQuestion()).toLower()) {
				currentState = STATE_FIRST_STEP;
				inTextType->setText("");
				SlotTypeMix();
			} else {
				tmpStringForOutput.sprintf( "%s - %s", testInterface.GetAnswer(), testInterface.GetQuestion() );
				outTextType->setText( tmpStringForOutput );
				inTextType->setText("");
			}
			break;
		case 2:
		case 3:
			if (inTextType->text().toLower() ==
			    QString(testInterface.GetAnswer()).toLower()) {
				currentState = STATE_FIRST_STEP;
				inTextType->setText("");
				SlotTypeMix();
			} else {
				tmpStringForOutput.sprintf( "%s - %s", testInterface.GetQuestion(), testInterface.GetAnswer() );
				outTextType->setText( tmpStringForOutput );
				inTextType->setText("");
			}
			break;
		}
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotNext() {
	switch( currenteTest ) {
	case TEST_QA:
		SlotQueAns();
		break;
	case TEST_AQ:
		SlotAnsQue();
		break;
	case TEST_MIX:
		SlotMix();
		break;
	case TEST_TYPEQUESTION:
		SlotTypeQueAns();
		break;
	case TEST_TYPEANSWER:
		SlotTypeAnsQue();
		break;
	case TEST_TYPEMIX:
		SlotTypeMix();
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotNewFile() {
#if (defined Q_OS_WIN) || (defined Q_OS_LINUX)
	while ( true ) {
		QString path = QFileDialog::getOpenFileName(0, QObject::tr("Choose file with words"),
		                                            QDir::homePath(), QObject::tr("Text file (*.txt);;All (*.*)"), 0,
		                                            QFileDialog::DontUseNativeDialog | QFileDialog::DontUseSheet |
		                                            QFileDialog::DontUseCustomDirectoryIcons | QFileDialog::ReadOnly );
		if ( testInterface.OpenFile( path.toStdString().c_str() ) == -1 ) {
			QMessageBox::critical( this, "Error", "File is not available!" );
			break;
		}
		testInterface.ClearTest();
		if ( testInterface.ReadFile() == false ) {
			QMessageBox::critical( this, "Error", "File wrong!" );
			break;
		}
		break;
	}
#else
	if ( testInterface.OpenFile( "/mnt/sdcard/words.txt" ) ) {
		QMessageBox::critical( this, "Error", "Put your file to /mnt/sdcard/words.txt" );
		exit( -1 );
	}
	testInterface.ClearTest();
	testInterface.ReadFile();
#endif
}

void ucUiTestMaker::SlotManageDict() {
	QString tmpStringForOutput;
	stackedWidget->setCurrentIndex( 3 );
	testInterface.Init();
	// outTextDict->setText( "" );
	while ( !testInterface.NewWord() ) {
		tmpStringForOutput.sprintf( "%s - %s", testInterface.GetQuestion(), testInterface.GetAnswer() );
		outTextDict->addItem( tmpStringForOutput );
	}
}
