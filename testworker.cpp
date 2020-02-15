#include <QFile>
#include <algorithm>

#include "testworker.h"
#include "jsonparser.h"
#include "global.h"
#include "debug_page.h"

/**
 * Constructor
 */

TestWorker::TestWorker() {
	_listData.clear();
	_mix_phase = MIX_PHASE_FIRST;
	_currentIndex = 0;
	_openFileName = "";
}

bool TestWorker::ReadFromFile( const QString &filename ) {
	bool    ret;
	QString textFromFile;
	QFile   testFile;

	testFile.setFileName( filename );
	ret = testFile.open( QIODevice::ReadOnly );
	if ( ret == false ) {
		pDebug.Print( "ReadFromFile(): Can't open file, don't exist!" );
		return false;
	}
	textFromFile = testFile.readAll();
	testFile.close();

	if ( textFromFile.length() == 0 ) {
		pDebug.Print(
		    "ReadFromFile(): Can't read data, file is Empty!" );
		return false;
	}

	QList< struct Question > list;
	list = JsonParser::ParseJsonToQuestionsList( textFromFile.toUtf8() );

	if ( list.length() == 0 ) {
		pDebug.Print( "ReadFromFile(): Can't parse file!" );
		return false;
	}

	FlushData();
	foreach ( struct Question question, list ) {
		struct TestElement testElement;
		testElement._question = question;
		testElement._flag = FLAGSTATE_NOTSET;
		_listData.append( testElement );
	}
	_openFileName = filename;
	pDebug.Print( "Open: " + filename );
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
			return QString::number( _currentIndex + 1 ) + "/" +
			       QString::number( _listData.length() * 2 );
		case MIX_PHASE_SECOND:
			return QString::number( _currentIndex + 1 +
			                        _listData.length() ) +
			       "/" + QString::number( _listData.length() * 2 );
		default:
			pDebug.Print(
			    "GetIndexString(): Wrong _mix_phase value!" );
			return "";
		}
	} else {
		return QString::number( _currentIndex + 1 ) + "/" +
		       QString::number( _listData.length() );
	}
}

QString TestWorker::GetQuestion( bool random ) {
	if ( _currentIndex < 0 ) {
		pDebug.Print( "GetQuestion(): _currentIndex < 0!" );
		return "";
	}
	if ( _currentIndex >= _listData.length() ) {
		pDebug.Print( "GetQuestion(): _currentIndex > length!" );
		return "";
	}

	if ( random ) {
		switch ( GetRandFlag() ) {
		case FLAGSTATE_AQ: return GetAnswer();
		case FLAGSTATE_QA: return GetQuestion();
		default:
			pDebug.Print(
			    "GetQuestion(): Wrong GetRandFlag() value!" );
			return "";
		}
	} else {
		return _listData[ _currentIndex ]._question._question;
	}
}

QString TestWorker::GetAnswer( bool random ) {
	if ( _currentIndex < 0 ) {
		pDebug.Print( "GetAnswer(): _currentIndex < 0!" );
		return "";
	}
	if ( _currentIndex >= _listData.length() ) {
		pDebug.Print( "GetAnswer(): _currentIndex > length!" );
		return "";
	}

	if ( random ) {
		switch ( GetRandFlag() ) {
		case FLAGSTATE_AQ: return GetQuestion();
		case FLAGSTATE_QA: return GetAnswer();
		default:
			pDebug.Print(
			    "GetAnswer(): Wrong GetRandFlag() value!" );
			return "";
		}
	} else {
		return _listData[ _currentIndex ]._question._answer;
	}
}

bool TestWorker::Next( bool random ) {
	_currentIndex++;

	if ( _currentIndex < 0 ) {
		pDebug.Print( "Next(): _currentIndex < 0!" );
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
		default:
			pDebug.Print( "Next(): Wrong _mix_phase value!" );
			return false;
		}
	} else {
		if ( _currentIndex >= _listData.length() ) {
			return false;
		}
	}

	return true;
}

int TestWorker::GetLength( void ) const { return _listData.length(); }

QString TestWorker::GetQuestionByIndex( int index ) const {
	if ( index < 0 ) {
		pDebug.Print( "GetQuestionByIndex(): index < 0!" );
		return "";
	}
	if ( index >= _listData.length() ) {
		pDebug.Print( "GetQuestionByIndex(): index > length!" );
		return "";
	}

	return _listData[ index ]._question._question;
}

QString TestWorker::GetAnswerByIndex( int index ) const {
	if ( index < 0 ) {
		pDebug.Print( "GetAnswerByIndex(): index < 0!" );
		return "";
	}
	if ( index >= _listData.length() ) {
		pDebug.Print( "GetAnswerByIndex(): index > length!" );
		return "";
	}

	return _listData[ index ]._question._answer;
}

bool TestWorker::DeleteItemByIndex( int index ) {
	if ( index < 0 ) {
		pDebug.Print( "DeleteItemByIndex(): index < 0!" );
		return false;
	}
	if ( index >= _listData.length() ) {
		pDebug.Print( "DeleteItemByIndex(): index > length!" );
		return false;
	}

	_listData.removeAt( index );
	return true;
}

bool TestWorker::AddItem( QString question, QString answer ) {
	struct TestElement testElement;
	testElement._question._question = question;
	testElement._question._answer = answer;
	testElement._flag = FLAGSTATE_NOTSET;
	_listData.append( testElement );
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
		default:
			pDebug.Print( "GetRandFlag(): Wrong _flag value!" );
			return FLAGSTATE_NOTSET;
		}
	default:
		pDebug.Print( "GetRandFlag(): Wrong _mix_phase value!" );
		return FLAGSTATE_NOTSET;
	}
}

void TestWorker::FlushData() {
	_listData.clear();
	_openFileName = "";
}

void TestWorker::Shuffle() {
	time_t time{0};
	std::srand( unsigned( std::time( &time ) ) );
	std::random_shuffle( _listData.begin(), _listData.end() );
}
