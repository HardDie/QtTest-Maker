#include "uitestmaker.h"

ucUiTestMaker::ucUiTestMaker( QWidget* parent ) : QDialog( parent ) {
	setWindowTitle( "TestMaker" );
	//mainWindow = this;

		// Инициализация строк
	labelFreeLine	=	new QLabel( "" );
	labelFreeLine2	=	new QLabel( "" );
	outCounter		=	new QLabel;
	outTextQueAns	=	new QTextEdit;
	outTextQueAns->setDisabled( true );
	outTextQueAns->setFontPointSize( 15 );
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
	QPushButton  *  buttonMainMenu;
	QPushButton  *  buttonFontIncrease;
	QPushButton  *  buttonFontDecrease;

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
	buttonMainMenu     = new QPushButton( "Main menu" );
	buttonFontDecrease = new QPushButton( "-" );
	buttonFontIncrease = new QPushButton( "+" );

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
		layoutMainMenu->addWidget( labelFreeLine );
	widgetMainMenu->setLayout( layoutMainMenu );

		// Инициализация слоя для теста по типу следующее слово
	QWidget* widgetNextWord = new QWidget;
	QVBoxLayout* layoutNextWord = new QVBoxLayout;
	layoutNextWord->addWidget( outCounter );
		layoutNextWord->addWidget( labelFreeLine2 );
	layoutNextWord->addWidget( outTextQueAns );
		layoutNextWord->addWidget( labelFreeLine2 );
	layoutNextWord->addWidget( buttonNext );
	layoutNextWord->addWidget( buttonMainMenu );
	QHBoxLayout* layoutFontSize = new QHBoxLayout;
	layoutFontSize->addWidget( buttonFontDecrease );
	layoutFontSize->addWidget( buttonFontIncrease );
	layoutNextWord->addLayout( layoutFontSize );
		layoutNextWord->addWidget( labelFreeLine2 );
	widgetNextWord->setLayout( layoutNextWord );

		// Подключаем сигналы
	connect( buttonQueAns,      SIGNAL( clicked( bool ) ), this, SLOT( SlotQueAns() ) );
	connect( buttonAnsQue,      SIGNAL( clicked( bool ) ), this, SLOT( SlotAnsQue() ) );
	connect( buttonMix,         SIGNAL( clicked( bool ) ), this, SLOT( SlotMix() ) );
	connect( buttonTypeQueAns,  SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeQueAns() ) );
	connect( buttonTypeAnsQue,  SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeAnsQue() ) );
	connect( buttonTypeMix,     SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeMix() ) );
	connect( buttonNext,        SIGNAL( clicked( bool ) ), this, SLOT( SlotNext() ) );
	connect( buttonFontIncrease,SIGNAL( clicked( bool ) ), this, SLOT( SlotIncreaseFont() ) );
	connect( buttonFontDecrease,SIGNAL( clicked( bool ) ), this, SLOT( SlotDecreaseFont() ) );
	connect( buttonMainMenu,    SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );
	connect( buttonNewFile,     SIGNAL( clicked( bool ) ), this, SLOT( SlotNewFile() ) );
	connect( buttonExit,        SIGNAL( clicked( bool ) ), this, SLOT( close() ) );

		// Инициализируем стэк виджетов
	stackedWidget = new QStackedWidget;
	stackedWidget->addWidget( widgetMainMenu );
	stackedWidget->addWidget( widgetNextWord );


	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addWidget( stackedWidget );
	setLayout( layoutMain );
}

void ucUiTestMaker::SlotDecreaseFont() {
	qreal size = outTextQueAns->fontPointSize();
	if ( size >= 10 ) {
		size -= 5;
	}
	if ( size <= 10 ) size = 10;
	outTextQueAns->setFontPointSize( size );
	// Сделано, для обновления текста в окне после изменения шрифта
	QString tmp = outTextQueAns->toPlainText();
	outTextQueAns->setText( tmp );
}

void ucUiTestMaker::SlotIncreaseFont() {
	qreal size = outTextQueAns->fontPointSize();
	if ( size <= 50 ) {
		size += 5;
	}
	if ( size > 50 ) size = 50;
	outTextQueAns->setFontPointSize( size );
	// Сделано, для обновления текста в окне после изменения шрифта
	QString tmp = outTextQueAns->toPlainText();
	outTextQueAns->setText( tmp );
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
	case STATE_FIRST_STEP:
		if ( testInterface.NewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() );
		outCounter->setText( tmpStringForOutput );
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
	case STATE_FIRST_STEP:
		if ( testInterface.NewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() );
		outCounter->setText( tmpStringForOutput );
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
	case STATE_FIRST_STEP:
		if ( testInterface.MixNewWord() ) {
			SlotMenu();
			return;
		}
		tmpStringForOutput.sprintf( "%d/%d", testInterface.GetCounter(), testInterface.GetLength() * 2 );
		outCounter->setText( tmpStringForOutput );
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
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
}

void ucUiTestMaker::SlotTypeAnsQue() {
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
	}
}

void ucUiTestMaker::SlotTypeMix() {
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
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
	if ( testInterface.OpenFile( "/mnt/sdcard/gg.txt" ) ) {
		QMessageBox::critical( this, "Error", "Incorrect file name or the file is not available!" );
		exit( -1 );
	}
	testInterface.ClearTest();
	testInterface.ReadFile();
#endif
}
