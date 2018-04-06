#include "uitestmaker.h"

ucUiTestMaker::ucUiTestMaker( QWidget* parent ) : QDialog( parent ) {
	setWindowTitle( "TestMaker" );

	// Инициализация сторки номера вопроса
	outCounter[0]    =  new QLabel;
	outCounter[1]    =  new QLabel;
	// Инициализация окон вывода вопроса
	outTextQueAns    =  new QTextEdit;
	outTextType      =  new QTextEdit;
	outTextDict      =  new QListWidget;
	outFileList      =  new QListWidget;
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

	// Путь до директории в которой хранятся все тесты
	pathToDict = "/mnt/sdcard/.dictionary/";

	InitAllObjects();
	SlotOpenNewFile();
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
	InitOpenNewFile();

	QVBoxLayout* layoutMain = new QVBoxLayout;
	layoutMain->addWidget( stackedWidget );
	setLayout( layoutMain );
}

/* ##### Тест: просмотр ##### */
void ucUiTestMaker::SlotQueAns() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
		return;
	}
	if ( testInterface.GetLength() == 0 ) {
		QMessageBox::information( this, "Empty", "Dictionary is empty!\nAdd at least one question in \"Manage dictionary\"" );
		SlotMenu();
		return;
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( WIDGET_SHOW_TEST );
		testInterface.ClearFlags();
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
	if ( testInterface.GetLength() == 0 ) {
		QMessageBox::information( this, "Empty", "Dictionary is empty!\nAdd at least one question in \"Manage dictionary\"" );
		SlotMenu();
		return;
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( WIDGET_SHOW_TEST );
		testInterface.ClearFlags();
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
	if ( testInterface.GetLength() == 0 ) {
		QMessageBox::information( this, "Empty", "Dictionary is empty!\nAdd at least one question in \"Manage dictionary\"" );
		SlotMenu();
		return;
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( WIDGET_SHOW_TEST );
		testInterface.ClearFlags();
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

/* ##### Тест: набор ##### */
void ucUiTestMaker::SlotTypeQueAns() {
	QString tmpStringForOutput;
	if ( testInterface.FileIsOpen() == false ) {
		QMessageBox::critical( this, "Error", "Test not open!" );
		SlotMenu();
		return;
	}
	if ( testInterface.GetLength() == 0 ) {
		QMessageBox::information( this, "Empty", "Dictionary is empty!\nAdd at least one question in \"Manage dictionary\"" );
		SlotMenu();
		return;
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( WIDGET_TYPE_TEST );
		testInterface.ClearFlags();
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
	if ( testInterface.GetLength() == 0 ) {
		QMessageBox::information( this, "Empty", "Dictionary is empty!\nAdd at least one question in \"Manage dictionary\"" );
		SlotMenu();
		return;
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( WIDGET_TYPE_TEST );
		testInterface.ClearFlags();
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
	if ( testInterface.GetLength() == 0 ) {
		QMessageBox::information( this, "Empty", "Dictionary is empty!\nAdd at least one question in \"Manage dictionary\"" );
		SlotMenu();
		return;
	}
	switch ( currentState ) {
	case STATE_INIT:
		stackedWidget->setCurrentIndex( WIDGET_TYPE_TEST );
		testInterface.ClearFlags();
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

/* ##### Слоты управления ##### */
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
void ucUiTestMaker::SlotMenu() {
	stackedWidget->setCurrentIndex( WIDGET_MAIN_MENU );
	currentState = STATE_INIT;
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

/* ##### Открытие нового файла ##### */
static void RedrawFilesList( QString pathToDict,
                             QListWidget* outFileList ) {
	QDir dir( pathToDict );
	dir.setFilter( QDir::Files );

	outFileList->clear();
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); i++) {
		QFileInfo fileInfo = list.at( i );
		outFileList->addItem( fileInfo.fileName() );
	}
}
void ucUiTestMaker::SlotOpenNewFile() {
	#if defined ANDROID
	if ( !QDir( pathToDict ).exists() ) {
		QMessageBox::StandardButton ans;
		ans = QMessageBox::question( this, "New save", "Can't find save folder, do you want create new?\n" + pathToDict );
		if ( ans == QMessageBox::Yes ) {
			QDir().mkdir( pathToDict );
		} else {
			exit( -1 );
		}
	}

	if ( outFileList->currentRow() == -1 ) {
		testInterface.ClearTest();
		stackedWidget->setCurrentIndex( WIDGET_OPEN_FILE );
		RedrawFilesList( pathToDict, outFileList );
	} else {
		QString filename = outFileList->currentItem()->text();
		if ( testInterface.CheckFile( pathToDict + filename ) == -1 ) {
			QMessageBox::critical( this, "Error", "File is not available!" );
			return;
		}
		if ( testInterface.ReadFile( pathToDict + filename ) == false ) {
			QMessageBox::critical( this, "Error", "File wrong!" );
			return;
		}
		SlotMenu();
		outFileList->clear();
	}
	#else
	while ( true ) {
		QString path = QFileDialog::getOpenFileName(0, QObject::tr("Choose file with words"),
		                                            QDir::homePath(), QObject::tr("Text file (*.json);;All (*.*)"), 0,
		                                            QFileDialog::DontUseNativeDialog | QFileDialog::DontUseSheet |
		                                            QFileDialog::DontUseCustomDirectoryIcons | QFileDialog::ReadOnly );
		if ( testInterface.CheckFile( path.toStdString().c_str() ) == -1 ) {
			QMessageBox::critical( this, "Error", "File is not available!" );
			break;
		}
		testInterface.ClearTest();
		if ( testInterface.ReadFile( path.toStdString().c_str() ) == false ) {
			QMessageBox::critical( this, "Error", "File wrong!" );
			break;
		}
		break;
	}
	#endif
}
void ucUiTestMaker::SlotDeleteFile() {
	if ( outFileList->currentRow() == -1 ) {
		QMessageBox::information( this, "Choose file", "You should choose file for delete" );
		return;
	}

	QString filename = outFileList->currentItem()->text();

	QMessageBox::StandardButton ans;
	ans = QMessageBox::question( this, "Delete file", "Are you sure what you want delete \"" + filename +  "\" file?" );
	if ( ans == QMessageBox::No ) {
		return;
	}

	QFile file( pathToDict + filename );
	file.remove();
	RedrawFilesList( pathToDict, outFileList );
}
void ucUiTestMaker::SlotCreateFile() {
	bool ok;
	QString filename = QInputDialog::getText(this, tr("Create new dictionary"), tr("File name:"), QLineEdit::Normal, "", &ok);
	if ( !ok ) {
		return;
	}
	if ( filename.isEmpty() ) {
		QMessageBox::information( this, "Wrong name", "File name is empty." );
		return;
	}

	filename += ".json";
	QFile file( pathToDict + filename );
	if ( file.exists() ) {
		QMessageBox::information( this, "Wrong name", "File with name \"" + filename + "\" already exist.\nChoose another name or delete exist file." );
		return;
	}

	if ( !file.open( QIODevice::WriteOnly ) ) {
		QMessageBox::critical( this, "Error", "Can't create file" );
		return;
	}
	file.close();
	testInterface.InitEmptyFile( pathToDict + filename );
	RedrawFilesList( pathToDict, outFileList );
}

/* ##### Управление словарем ##### */
static void RedrawWordsList( uns::ucTestMaker* testInterface,
                             QListWidget* outTextDict ) {
	outTextDict->clear();
	for ( int i = 0; i < testInterface->GetLength(); i++ ) {
		outTextDict->addItem( testInterface->GetQuestion( i ) + " - " +
		                      testInterface->GetAnswer( i ) );
	}
}
void ucUiTestMaker::SlotManageDict() {
	QString tmpStringForOutput;
	stackedWidget->setCurrentIndex( WIDGET_DICT_MANAGE );
	RedrawWordsList( &testInterface, outTextDict );
}
void ucUiTestMaker::SlotAddNewQuestion() {
	if ( inTextDict[0]->text() != "" &&
	    inTextDict[1]->text() != "" ) {
		testInterface.AddNewQuestion( inTextDict[0]->text(), inTextDict[1]->text() );
		inTextDict[0]->setText( "" );
		inTextDict[1]->setText( "" );
		RedrawWordsList( &testInterface, outTextDict );
	} else {
		QMessageBox::warning( this, "Warning", "Input box is empty" );
	}
}
void ucUiTestMaker::SlotDeleteQuestion() {
	if ( outTextDict->currentRow() != -1 ) {
		testInterface.DeleteQuestion( outTextDict->currentRow() );
		RedrawWordsList( &testInterface, outTextDict );
	} else {
		QMessageBox::warning( this, "Warning", "Select line for delete" );
	}
}
void ucUiTestMaker::SlotEditQuestion() {
	if ( outTextDict->currentRow() != -1 ) {
		inTextDict[0]->setText( testInterface.GetQuestion( outTextDict->currentRow() ) );
		inTextDict[1]->setText( testInterface.GetAnswer( outTextDict->currentRow() ) );
		testInterface.DeleteQuestion( outTextDict->currentRow() );
		RedrawWordsList( &testInterface, outTextDict );
	} else {
		QMessageBox::warning( this, "Warning", "Select line for edit" );
	}
}
void ucUiTestMaker::SlotSaveDictionary() {
	if ( testInterface.SaveFile() ) {
		QMessageBox::information( this, "Succesfull", "Dictionary was saved" );
	} else {
		QMessageBox::critical( this, "Error", "File not set or corrupt" );
	}
}
