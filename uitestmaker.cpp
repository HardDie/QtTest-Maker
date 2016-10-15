#include "uitestmaker.h"

ucUiTestMaker::ucUiTestMaker( QWidget* parent ) : QDialog( parent ) {
	setWindowTitle( "TestMaker" );
	//mainWindow = this;

		// Инициализация строк
	labelFreeLine	=	new QLabel( "" );
	labelCounter	=	new QLabel;
	labelTextQueAns	=	new QLabel;

	if ( testInterface.OpenFile( "gg.txt" ) ) {
		QMessageBox msgError;
		msgError.setText( "Incorrect file name or the file is not available!" );
		msgError.exec();
		exit( -1 );
	}
	testInterface.ClearTest();
	testInterface.ReadFile();

	InitAllObjects();
	currentState = STATE_INIT;
}

ucUiTestMaker::~ucUiTestMaker() {

}

/*
====================
InitAllObjects

	Инициализация всех обьуектов, создание виджетов, привязка сигналов к слотам
====================
*/
void ucUiTestMaker::InitAllObjects() {
	QPushButton		*	buttonQueAns;
	QPushButton		*	buttonAnsQue;
	QPushButton		*	buttonMix;
	QPushButton		*	buttonTypeQueAns;
	QPushButton		*	buttonTypeAnsQue;
	QPushButton		*	buttonTypeMix;
	QPushButton		*	buttonNewFile;
	QPushButton		*	buttonExit;
	QPushButton		*	buttonNext;
	QPushButton		*	buttonMainMenu;

		// Инициализация кнопок
	buttonQueAns	=	new QPushButton( "Question -> Answer" );
	buttonAnsQue	=	new QPushButton( "Answer -> Question" );
	buttonMix		=	new QPushButton( "Mix" );
	buttonTypeQueAns=	new QPushButton( "Type Question -> Answer" );
	buttonTypeAnsQue=	new QPushButton( "Type Answer -> Question" );
	buttonTypeMix	=	new QPushButton( "Type mix" );
	buttonNewFile	=	new QPushButton( "Open new file" );
	buttonExit		=	new QPushButton( "Exit" );
	buttonNext		=	new QPushButton( "Next" );
	buttonMainMenu	=	new QPushButton( "Main menu" );

		// Инициализация слоя главного меню
	QWidget* widgetMainMenu = new QWidget;
	QVBoxLayout* layoutMainMenu = new QVBoxLayout;
	layoutMainMenu->addWidget( buttonQueAns );
	layoutMainMenu->addWidget( buttonAnsQue );
	layoutMainMenu->addWidget( buttonMix );
		layoutMainMenu->addWidget( labelFreeLine );
	layoutMainMenu->addWidget( buttonTypeQueAns );
	layoutMainMenu->addWidget( buttonTypeAnsQue );
	layoutMainMenu->addWidget( buttonTypeMix );
		layoutMainMenu->addWidget( labelFreeLine );
	layoutMainMenu->addWidget( buttonNewFile );
	layoutMainMenu->addWidget( buttonExit );
	widgetMainMenu->setLayout( layoutMainMenu );

		// Инициализация слоя для теста по типу следующее слово
	QWidget* widgetNextWord = new QWidget;
	QVBoxLayout* layoutNextWord = new QVBoxLayout;
	layoutNextWord->addWidget( labelCounter );
	layoutNextWord->addWidget( labelTextQueAns );
	layoutNextWord->addWidget( buttonNext );
	layoutNextWord->addWidget( buttonMainMenu );
	widgetNextWord->setLayout( layoutNextWord );

		// Подключаем сигналы
	connect( buttonQueAns,		SIGNAL( clicked( bool ) ), this, SLOT( SlotQueAns() ) );
	connect( buttonAnsQue,		SIGNAL( clicked( bool ) ), this, SLOT( SlotAnsQue() ) );
	connect( buttonMix,			SIGNAL( clicked( bool ) ), this, SLOT( SlotMix() ) );
	connect( buttonTypeQueAns,	SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeQueAns() ) );
	connect( buttonTypeAnsQue,	SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeAnsQue() ) );
	connect( buttonTypeMix,		SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeMix() ) );
	connect( buttonNext,		SIGNAL( clicked( bool ) ), this, SLOT( SlotNext() ) );
	connect( buttonMainMenu,	SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );
	connect( buttonExit,		SIGNAL( clicked( bool ) ), this, SLOT( close() ) );

		// Инициализируем стэк виджетов
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget( widgetMainMenu );
	stackedWidget->addWidget( widgetNextWord );


	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addWidget( stackedWidget );
	setLayout( layoutMain );
}

void ucUiTestMaker::SlotMenu() {
	stackedWidget->setCurrentIndex( 0 );
	currentState = STATE_INIT;
}

void ucUiTestMaker::SlotQueAns() {
	QString tmpStringForOutput;
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( 1 );
		testInterface.Init();
		currentState = STATE_FIRST_STEP;
		currenteTest = TEST_QA;
	case STATE_FIRST_STEP:
		testInterface.NewWord();
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() );
		labelCounter->setText( tmpStringForOutput );
		tmpStringForOutput.sprintf( "%s", testInterface.GetQuestion() );
		labelTextQueAns->setText( tmpStringForOutput );
		currentState = STATE_SECOND_STEP;
		break;
	case STATE_SECOND_STEP:
		tmpStringForOutput.sprintf( "%s - %s", testInterface.GetQuestion(), testInterface.GetAnswer() );
		//tmpStringForOutput.sprintf( "%s - %s", "Hello", "Привет" );
		labelTextQueAns->setText( tmpStringForOutput );
		currentState = STATE_FIRST_STEP;
		break;
	default:
		break;
	}
}

void ucUiTestMaker::SlotAnsQue() {
	stackedWidget->setCurrentIndex( 1 );
}

void ucUiTestMaker::SlotMix() {
	stackedWidget->setCurrentIndex( 1 );
}

void ucUiTestMaker::SlotTypeQueAns() {

}

void ucUiTestMaker::SlotTypeAnsQue() {

}

void ucUiTestMaker::SlotTypeMix() {

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
	default:
		break;
	}
}
