#include <QDebug>

#include "guiworker.h"

GUIWorker::GUIWorker( QObject *parent ) : QObject( parent ) {
	_testWorker.ReadFromFile( "/home/harddie/new.json" );
}

void GUIWorker::setTestModeQA() {
	_testWorker.FlushFlags();
	_testWorker.SetTestMode( TESTMODE_QA );
	nextTestStep();
}
void GUIWorker::setTestModeAQ() {
	_testWorker.FlushFlags();
	_testWorker.SetTestMode( TESTMODE_AQ );
	nextTestStep();
}
void GUIWorker::setTestModeMix() {
	_testWorker.FlushFlags();
	_testWorker.SetTestMode( TESTMODE_MIX );
	nextTestStep();
}

void GUIWorker::setTestModeTypeQA() {
	_testWorker.FlushFlags();
	_testWorker.SetTestMode( TESTMODE_TYPE_QA );
}
void GUIWorker::setTestModeTypeAQ() {
	_testWorker.FlushFlags();
	_testWorker.SetTestMode( TESTMODE_TYPE_AQ );
}
void GUIWorker::setTestModeTypeMix() {
	_testWorker.FlushFlags();
	_testWorker.SetTestMode( TESTMODE_TYPE_MIX );
}

void GUIWorker::nextTestStep() {
	QString resultString;
	QString indexString;
	indexString = _testWorker.GetIndexString();
	if ( _testWorker.GetString( resultString ) == false ) {
		emit returnToMainMenu();
		return;
	}
	// В режиме Mix в момент когда мы первый раз прошлись по списку
	// индекс стоит невалидный и до вызова GetString будет возвращаться
	// пустая строка для этого поврторно вызываем после GetString
	if ( indexString.length() == 0 ) {
		indexString = _testWorker.GetIndexString();
	}
	emit setTestString( resultString, indexString );
}
