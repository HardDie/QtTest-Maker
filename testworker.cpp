#include <QFile>
#include <algorithm>
#include <QDebug>

#include "testworker.h"
#include "jsonparser.h"
#include "global.h"

TestWorker::TestWorker() {
	_listData.clear();
	_phase = PHASE_FIRST;
	_mix_phase = MIX_PHASE_FIRST;
	_testmode = TESTMODE_NOTSET;
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
		testElement._flag = FLAGSTATE_NONE;
		_listData.append( testElement );
	}
	return true;
}

void TestWorker::SetTestMode( testmode_t testmode ) {
	switch ( testmode ) {
	case TESTMODE_QA: qDebug() << "Set QA mode"; break;
	case TESTMODE_AQ: qDebug() << "Set AQ mode"; break;
	case TESTMODE_MIX: qDebug() << "Set Mix mode"; break;
	case TESTMODE_TYPE_QA: qDebug() << "Set Type QA mode"; break;
	case TESTMODE_TYPE_AQ: qDebug() << "Set Type AQ mode"; break;
	case TESTMODE_TYPE_MIX: qDebug() << "Set Type Mix mode"; break;
	case TESTMODE_NOTSET: qDebug() << "ERROR: Set not valid mode"; break;
	}
	_testmode = testmode;
}

void TestWorker::FlushFlags() {
	foreach ( struct TestElement element, _listData ) {
		element._flag = FLAGSTATE_NONE;
	}
	_currentIndex = 0;
	_phase = PHASE_FIRST;
	_mix_phase = MIX_PHASE_FIRST;
	Shuffle();
}

bool TestWorker::GetString( QString &resultString ) {
	switch ( _testmode ) {
	case TESTMODE_QA: return GetQAString( resultString );
	case TESTMODE_AQ: return GetAQString( resultString );
	case TESTMODE_MIX: return GetMixString( resultString );
	case TESTMODE_TYPE_QA: break;
	case TESTMODE_TYPE_AQ: break;
	case TESTMODE_TYPE_MIX: break;
	case TESTMODE_NOTSET: qDebug() << "ERROR: Not valid test mode"; break;
	}
	return false;
}

QString TestWorker::GetIndexString() {
	if ( ValidateIndex() ) {
		if ( _testmode == TESTMODE_MIX ||
		     _testmode == TESTMODE_TYPE_MIX ) {
			if ( _mix_phase == MIX_PHASE_FIRST ) {
				return QString::number( _currentIndex + 1 ) +
				       "/" +
				       QString::number( _listData.length() *
				                        2 );
			} else if ( _mix_phase == MIX_PHASE_SECOND ) {
				return QString::number( _listData.length() +
				                        _currentIndex + 1 ) +
				       "/" +
				       QString::number( _listData.length() *
				                        2 );
			}
		} else {
			return QString::number( _currentIndex + 1 ) + "/" +
			       QString::number( _listData.length() );
		}
	}
	return QString();
}

// Private

bool TestWorker::GetQAString( QString &resultString ) {
	if ( _currentIndex < 0 ) {
		qDebug() << "ERROR: QA Wrong index!";
		return false;
	}
	if ( _listData.length() == 0 ) {
		qDebug() << "ERROR: QA data is empty!";
		return false;
	}
	switch ( _phase ) {
	case PHASE_NEXTWORD:
		if ( ValidateIndex() == false ) {
			qDebug() << "ERROR: QA List is over!";
			return false;
		}
		[[clang::fallthrough]];
	case PHASE_FIRST:
		_phase = PHASE_SECOND;
		resultString = _listData[ _currentIndex ]._question._question;
		break;
	case PHASE_SECOND:
		_phase = PHASE_NEXTWORD;
		resultString = _listData[ _currentIndex ]._question._question +
		               " - " +
		               _listData[ _currentIndex ]._question._answer;
		_currentIndex++;
		break;
	}
	return true;
}

bool TestWorker::GetAQString( QString &resultString ) {
	if ( _currentIndex < 0 ) {
		qDebug() << "ERROR: AQ Wrong index!";
		return false;
	}
	if ( _listData.length() == 0 ) {
		qDebug() << "ERROR: AQ data is empty!";
		return false;
	}
	switch ( _phase ) {
	case PHASE_NEXTWORD:
		if ( ValidateIndex() == false ) {
			qDebug() << "ERROR: AQ List is over!";
			return false;
		}
		[[clang::fallthrough]];
	case PHASE_FIRST:
		_phase = PHASE_SECOND;
		resultString = _listData[ _currentIndex ]._question._answer;
		break;
	case PHASE_SECOND:
		_phase = PHASE_NEXTWORD;
		resultString = _listData[ _currentIndex ]._question._answer +
		               " - " +
		               _listData[ _currentIndex ]._question._question;
		_currentIndex++;
		break;
	}
	return true;
}

bool TestWorker::GetMixString( QString &resultString ) {
	if ( _listData.length() == 0 ) {
		qDebug() << "ERROR: Mix data is empty!";
		return false;
	}

	switch ( _mix_phase ) {
	case MIX_PHASE_FIRST:
		if ( ValidateIndex() == false ) {
			_mix_phase = MIX_PHASE_SECOND;
			_currentIndex = 0;
			Shuffle();
			// Если просто выйти в этот момент, то в строке будет
			// пусто т.к. мы только сменили режим Чтобы этого не
			// произошло, мы снова вызываем эту же функцию только
			// уже с новым режимом
			return GetMixString( resultString );
		}

		if ( _listData[ _currentIndex ]._flag == FLAGSTATE_NONE ) {
			_listData[ _currentIndex ]._flag =
			    rand() % 2 ? FLAGSTATE_AQ : FLAGSTATE_QA;
		}

		switch ( _listData[ _currentIndex ]._flag ) {
		case FLAGSTATE_AQ: return GetAQString( resultString ); ;
		case FLAGSTATE_QA: return GetQAString( resultString );
		case FLAGSTATE_NONE:
			qDebug() << "ERROR: Mix wrong flagstate!";
			return false;
		}
		break;
	case MIX_PHASE_SECOND:
		if ( ValidateIndex() == false ) {
			return false;
		}

		switch ( _listData[ _currentIndex ]._flag ) {
		case FLAGSTATE_AQ: return GetQAString( resultString );
		case FLAGSTATE_QA: return GetAQString( resultString );
		case FLAGSTATE_NONE:
			qDebug() << "ERROR: Mix wrong flagstate!";
			return false;
		}
		break;
	}

	return false;
}

void TestWorker::FlushData() { _listData.clear(); }

void TestWorker::Shuffle() {
	time_t time{0};
	std::srand( unsigned( std::time( &time ) ) );
	std::random_shuffle( _listData.begin(), _listData.end() );
}

bool TestWorker::Next() {
	_currentIndex++;

	if ( _currentIndex < 0 || _currentIndex >= _listData.length() ) {
		return false;
	}

	return true;
}

bool TestWorker::ValidateIndex() {
	if ( _currentIndex < 0 || _currentIndex >= _listData.length() ) {
		return false;
	}

	return true;
}
// JsonParser::FormatJsonFileFromQuestionList(_listData);
