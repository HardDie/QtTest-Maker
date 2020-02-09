#include <QFile>
#include <algorithm>
#include <QDebug>

#include "testworker.h"
#include "jsonparser.h"
#include "global.h"

/**
 * Constructor
 */

TestWorker::TestWorker() {
	_listData.clear();
	_mix_phase = MIX_PHASE_FIRST;
	_currentIndex = 0;
}

bool TestWorker::ReadFromFile( const QString &filename ) {
	bool    ret;
	QString textFromFile;
	QFile   testFile;

	testFile.setFileName( filename );
	ret = testFile.open( QIODevice::ReadOnly );
	if ( ret == false ) {
		qDebug() << "ERROR: Can't open file, don't exist!";
		return false;
	}
	textFromFile = testFile.readAll();
	testFile.close();

	if ( textFromFile.length() == 0 ) {
		qDebug() << "ERROR: Can't read data, file is Empty!";
		return false;
	}

	QList< struct Question > list;
	list = JsonParser::ParseJsonToQuestionsList( textFromFile.toUtf8() );

	if ( list.length() == 0 ) {
		qDebug() << "ERROR: Can't parse file!";
		return false;
	}

	FlushData();
	foreach ( struct Question question, list ) {
		struct TestElement testElement;
		testElement._question = question;
		testElement._flag = FLAGSTATE_NOTSET;
		_listData.append( testElement );
	}
	return true;
}

void TestWorker::FlushFlags() {
	foreach ( struct TestElement element, _listData ) {
		element._flag = FLAGSTATE_NOTSET;
	}
	_currentIndex = 0;
	_mix_phase = MIX_PHASE_FIRST;
	Shuffle();
}

QString TestWorker::GetIndexString( bool random ) {
	if ( random ) {
		switch ( _mix_phase ) {
		case MIX_PHASE_FIRST:
			return QString::number( _currentIndex + 1 ) +
			       "/" + QString::number( _listData.length() * 2 );
		case MIX_PHASE_SECOND:
			return QString::number( _currentIndex + 1 +
			                        _listData.length() ) +
			       "/" + QString::number( _listData.length() * 2 );
		default: assert( NULL );
		}
	} else {
		return QString::number( _currentIndex + 1 ) + "/" +
		       QString::number( _listData.length() );
	}
	assert( NULL );
}

QString TestWorker::GetQuestion( bool random ) {
	if ( random ) {
		switch ( GetRandFlag() ) {
		case FLAGSTATE_AQ: return GetAnswer();
		case FLAGSTATE_QA: return GetQuestion();
		default: qDebug() << "ERROR: Mix wrong flagstate!"; return "";
		}
	} else {
		return _listData[ _currentIndex ]._question._question;
	}
}

QString TestWorker::GetAnswer( bool random ) {
	if ( random ) {
		switch ( GetRandFlag() ) {
		case FLAGSTATE_AQ: return GetQuestion();
		case FLAGSTATE_QA: return GetAnswer();
		default: qDebug() << "ERROR: Mix wrong flagstate!"; return "";
		}
	} else {
		return _listData[ _currentIndex ]._question._answer;
	}
}

bool TestWorker::Next( bool random ) {
	_currentIndex++;

	if ( _currentIndex < 0 ) {
		return false;
	}

	if ( random ) {
		switch ( _mix_phase ) {
		case MIX_PHASE_FIRST:
			if ( _currentIndex >= _listData.length() ) {
				_currentIndex = 0;
				_mix_phase = MIX_PHASE_SECOND;
				Shuffle();
			}
			break;
		case MIX_PHASE_SECOND:
			if ( _currentIndex >= _listData.length() ) {
				return false;
			}
			break;
		default: assert( NULL );
		}
	} else {
		if ( _currentIndex >= _listData.length() ) {
			return false;
		}
	}

	return true;
}

/**
 * Private
 */

flagstate_t TestWorker::GetRandFlag() {
	switch ( _mix_phase ) {
	case MIX_PHASE_FIRST:
		if ( _listData[ _currentIndex ]._flag != FLAGSTATE_AQ &&
		     _listData[ _currentIndex ]._flag != FLAGSTATE_QA ) {
			_listData[ _currentIndex ]._flag =
			    rand() % 2 ? FLAGSTATE_AQ : FLAGSTATE_QA;
		}

		return _listData[ _currentIndex ]._flag;
	case MIX_PHASE_SECOND:
		// Invert values
		switch ( _listData[ _currentIndex ]._flag ) {
		case FLAGSTATE_AQ: return FLAGSTATE_QA;
		case FLAGSTATE_QA: return FLAGSTATE_AQ;
		default: return FLAGSTATE_NOTSET;
		}
	default: return FLAGSTATE_NOTSET;
	}
}

void TestWorker::FlushData() { _listData.clear(); }

void TestWorker::Shuffle() {
	time_t time{0};
	std::srand( unsigned( std::time( &time ) ) );
	std::random_shuffle( _listData.begin(), _listData.end() );
}
