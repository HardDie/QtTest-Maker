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
	stackedWidget = new QStackedWidget;

	InitMainMenu();
	InitNextWord();
	InitTypeAns();
	InitSetupDict();

	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addWidget( stackedWidget );
	setLayout( layoutMain );
}

static void ChangeFontSize( QTextEdit *textEdit, int diff ) {
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
		return;
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
		outTextQueAns->setText( testInterface.GetQuestion() + " - " + testInterface.GetAnswer() );
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
		return;
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
		outTextQueAns->setText( testInterface.GetAnswer() + " - " + testInterface.GetQuestion() );
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
		return;
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
			tmpStringForOutput = testInterface.GetAnswer() + " - " + testInterface.GetQuestion();
			outTextQueAns->setText( tmpStringForOutput );
			break;
		case 2:
		case 3:
			tmpStringForOutput = testInterface.GetQuestion() + " - " + testInterface.GetAnswer();
			outTextQueAns->setText( tmpStringForOutput );
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
		return;
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
			outTextType->setText( testInterface.GetQuestion() + " - " + testInterface.GetAnswer() );
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
		return;
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
			outTextType->setText( testInterface.GetAnswer() + " - " + testInterface.GetQuestion() );
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
		return;
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
				tmpStringForOutput = testInterface.GetAnswer() + " - " + testInterface.GetQuestion();
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
				tmpStringForOutput = testInterface.GetQuestion() + " - " + testInterface.GetAnswer();
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
		                                            QDir::homePath(), QObject::tr("Text file (*.json);;All (*.*)"), 0,
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

static void RedrawWordsList( uns::ucTestMaker* testInterface,
                             QListWidget* outTextDict) {
	outTextDict->clear();
	for ( int i = 0; i < testInterface->GetLength(); i++ ) {
		outTextDict->addItem( testInterface->GetQuestion( i ) + " - " +
		                      testInterface->GetAnswer( i ) );
	}
}

void ucUiTestMaker::SlotManageDict() {
	QString tmpStringForOutput;
	stackedWidget->setCurrentIndex( 3 );
	RedrawWordsList( &testInterface, outTextDict );
}

void ucUiTestMaker::SlotAddNewQue() {
	if ( inTextDict[0]->text() != "" &&
	    inTextDict[1]->text() != "" ) {
		testInterface.AddNewQue( inTextDict[0]->text(), inTextDict[1]->text() );
		inTextDict[0]->setText( "" );
		inTextDict[1]->setText( "" );
		RedrawWordsList( &testInterface, outTextDict );
	} else {
		QMessageBox::warning( this, "Warning", "Input box is empty" );
	}
}

void ucUiTestMaker::SlotDeleteQue() {
	if ( outTextDict->currentRow() != -1 ) {
		testInterface.DeleteQue( outTextDict->currentRow() );
		RedrawWordsList( &testInterface, outTextDict );
	} else {
		QMessageBox::warning( this, "Warning", "Select line for delete" );
	}
}

void ucUiTestMaker::SlotEditQue() {
	if ( outTextDict->currentRow() != -1 ) {
		inTextDict[0]->setText( testInterface.GetQuestion( outTextDict->currentRow() ) );
		inTextDict[1]->setText( testInterface.GetAnswer( outTextDict->currentRow() ) );
		testInterface.DeleteQue( outTextDict->currentRow() );
		RedrawWordsList( &testInterface, outTextDict );
	} else {
		QMessageBox::warning( this, "Warning", "Select line for edit" );
	}
}

void ucUiTestMaker::SlotSave() {
	if ( testInterface.SaveFile() ) {
		QMessageBox::information( this, "Succesfull", "Dictionary was saved" );
	} else {
		QMessageBox::critical( this, "Error", "File not set or corrupt" );
	}
}
