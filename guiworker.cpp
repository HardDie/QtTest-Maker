#include <QUrl>

#include "guiworker.h"
#include "debug_page.h"

/**
 * Constructor
 */

GUIWorker::GUIWorker( QObject *parent ) : QObject( parent ) {
	_phase = PHASE_NOTSET;
	_testmode = TESTMODE_NOTSET;
	_randmode = false;
}

/**
 * Setup functions
 */

void GUIWorker::setTestModeQA() {
	if ( _testWorker.GetLength() == 0 ) {
		emit qmlReturnToMainMenu();
		emit qmlShowMessage(
		    "Can't start test",
		    "Dictionary is empty of file is not opened!" );
		return;
	}

	_testWorker.FlushFlags();
	_testmode = TESTMODE_QA;
	_phase = PHASE_FIRST;
	_randmode = false;

	buttonTestNext();
}
void GUIWorker::setTestModeAQ() {
	if ( _testWorker.GetLength() == 0 ) {
		emit qmlReturnToMainMenu();
		emit qmlShowMessage(
		    "Can't start test",
		    "Dictionary is empty of file is not opened!" );
		return;
	}

	_testWorker.FlushFlags();
	_testmode = TESTMODE_AQ;
	_phase = PHASE_FIRST;
	_randmode = false;

	buttonTestNext();
}
void GUIWorker::setTestModeMix() {
	if ( _testWorker.GetLength() == 0 ) {
		emit qmlReturnToMainMenu();
		emit qmlShowMessage(
		    "Can't start test",
		    "Dictionary is empty of file is not opened!" );
		return;
	}

	_testWorker.FlushFlags();
	_testmode = TESTMODE_QA;
	_phase = PHASE_FIRST;
	_randmode = true;

	buttonTestNext();
}

void GUIWorker::setTestModeTypeQA() {
	if ( _testWorker.GetLength() == 0 ) {
		emit qmlReturnToMainMenu();
		emit qmlShowMessage(
		    "Can't start test",
		    "Dictionary is empty of file is not opened!" );
		return;
	}

	_testWorker.FlushFlags();
	_testmode = TESTMODE_QA;
	_phase = PHASE_FIRST;
	_randmode = false;

	buttonTestTypeCheck( "" );
}
void GUIWorker::setTestModeTypeAQ() {
	if ( _testWorker.GetLength() == 0 ) {
		emit qmlReturnToMainMenu();
		emit qmlShowMessage(
		    "Can't start test",
		    "Dictionary is empty of file is not opened!" );
		return;
	}

	_testWorker.FlushFlags();
	_testmode = TESTMODE_AQ;
	_phase = PHASE_FIRST;
	_randmode = false;

	buttonTestTypeCheck( "" );
}
void GUIWorker::setTestModeTypeMix() {
	if ( _testWorker.GetLength() == 0 ) {
		emit qmlReturnToMainMenu();
		emit qmlShowMessage(
		    "Can't start test",
		    "Dictionary is empty of file is not opened!" );
		return;
	}

	_testWorker.FlushFlags();
	_testmode = TESTMODE_QA;
	_phase = PHASE_FIRST;
	_randmode = true;

	buttonTestTypeCheck( "" );
}

/**
 * Button functions
 */

void GUIWorker::buttonTestNext() {
	QString sQuestion, sAnswer;
	QString sResult;
	QString sIndex;

	switch ( _phase ) {
	case PHASE_NEXTWORD:
		if ( false == _testWorker.Next( _randmode ) ) {
			emit qmlReturnToMainMenu();
			return;
		}
		[[clang::fallthrough]];
	case PHASE_FIRST:
		_phase = PHASE_SECOND;
		sQuestion = getQuestionWithMode();

		sResult = sQuestion;
		break;
	case PHASE_SECOND:
		_phase = PHASE_NEXTWORD;
		sQuestion = getQuestionWithMode();
		sAnswer = getAnswerWithMode();

		sResult = sQuestion + " - " + sAnswer;
		break;
	default:
		pDebug.Print( "buttonTestNext(): Wrong phase type!" );
		return;
	}

	sIndex = _testWorker.GetIndexString( _randmode );
	emit qmlSetTestString( sResult, sIndex );
}

void GUIWorker::buttonTestTypeSkip() {
	QString sQuestion;
	QString sIndex;

	if ( _testWorker.Next( _randmode ) == false ) {
		emit qmlReturnToMainMenu();
		return;
	}

	sQuestion = getQuestionWithMode();
	sIndex = _testWorker.GetIndexString( _randmode );

	emit qmlSetTypeTestString( sQuestion, sIndex );
}

void GUIWorker::buttonTestTypeCheck( QString userAnswer ) {
	QString sQuestion, sAnswer;
	QString sIndex;
	QString sResult;

begin:
	switch ( _phase ) {
	case PHASE_NEXTWORD:
		if ( false == _testWorker.Next( _randmode ) ) {
			emit qmlReturnToMainMenu();
			return;
		}
		[[clang::fallthrough]];
	case PHASE_FIRST:
		_phase = PHASE_SECOND;
		sQuestion = getQuestionWithMode();

		sResult = sQuestion;
		break;
	case PHASE_SECOND:
		sAnswer = getAnswerWithMode();
		if ( userAnswer.toLower() == sAnswer.toLower() ) {
			_phase = PHASE_NEXTWORD;

			goto begin;
		} else {
			sQuestion = getQuestionWithMode();
			sResult = sQuestion + " - " + sAnswer;
		}
		break;
	default:
		pDebug.Print( "buttonTestTypeCheck(): Wrong phase type!" );
		return;
	}

	sIndex = _testWorker.GetIndexString( _randmode );
	emit qmlSetTypeTestString( sResult, sIndex );
}

void GUIWorker::openFile( QString url ) {
	if ( QUrl( url ).isLocalFile() ) {
		_testWorker.ReadFromFile( QUrl( url ).toLocalFile() );
	} else {
		_testWorker.ReadFromFile( QUrl( url ).url() );
	}

	if ( _testWorker.GetLength() == 0 ) {
		emit qmlShowMessage( "ERROR",
		                     "File is broken or wrong format!" );
	}
}

void GUIWorker::saveFile() {
	bool ret;
	ret = _testWorker.SaveToFile();
	if ( ret == false ) {
		emit qmlShowMessage( "ERROR",
		                     "Can't save the file! The file may not be "
		                     "open, try Save as..." );
	}
}

void GUIWorker::saveFileAs( QString url ) {
	bool ret;
	if ( QUrl( url ).isLocalFile() ) {
		ret = _testWorker.SaveToFile( QUrl( url ).toLocalFile() );
	} else {
		ret = _testWorker.SaveToFile( QUrl( url ).url() );
	}
	if ( ret == false ) {
		emit qmlShowMessage( "ERROR",
		                     "Can't save the file! Permission denied!" );
	}
}

void GUIWorker::dictionaryFillList() const {
	int length = _testWorker.GetLength();
	for ( int i = 0; i < length; i++ ) {
		auto question = _testWorker.GetQuestionByIndex( i );
		auto answer = _testWorker.GetAnswerByIndex( i );
		emit qmlAddItemToList( question, answer );
	}
}

void GUIWorker::dictionaryDeleteItem( int index ) {
	_testWorker.DeleteItemByIndex( index );
}

void GUIWorker::dictionaryAddItem( QString question, QString answer ) {
	_testWorker.AddItem( question, answer );
}

void GUIWorker::exitFromApp() const {
	if ( _testWorker.IsDictionaryChanged() == true ) {
		emit qmlShowExitMessage(
		    "Unsaved changes!",
		    "You changed the dictionary and did not save the changes."
		    "Do you really want to leave?" );
		return;
	}
	emit qmlExitFromApp();
}

/**
 * Private
 */

QString GUIWorker::getQuestionWithMode( void ) {
	switch ( _testmode ) {
	case TESTMODE_QA: return _testWorker.GetQuestion( _randmode );
	case TESTMODE_AQ: return _testWorker.GetAnswer( _randmode );
	default:
		pDebug.Print( "getQuestionWithMode(): Wrong test mode!" );
		return "";
	}
}

QString GUIWorker::getAnswerWithMode( void ) {
	switch ( _testmode ) {
	case TESTMODE_QA: return _testWorker.GetAnswer( _randmode );
	case TESTMODE_AQ: return _testWorker.GetQuestion( _randmode );
	default:
		pDebug.Print( "getAnswerWithMode(): Wrong test mode!" );
		return "";
	}
}
