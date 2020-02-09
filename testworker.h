#ifndef TESTWORKER_H
#define TESTWORKER_H

#include <QString>
#include <QList>

#include "global.h"

struct TestElement {
	struct Question _question;
	flagstate       _flag;
};

class TestWorker {
public:
	TestWorker();
	bool ReadFromFile( const QString &filename );
	void SetTestMode( testmode_t testmode );
	void FlushFlags( void );

	bool    GetString( QString &resultString );
	QString GetIndexString( void );

private:
	QList< struct TestElement > _listData;
	int                         _currentIndex;
	phase_t                     _phase;
	testmode_t                  _testmode;
	mix_phase_t                 _mix_phase;

	bool GetQAString( QString &resultString );
	bool GetAQString( QString &resultString );
	bool GetMixString( QString &resultString );

	void FlushData( void );
	void Shuffle( void );
	bool Next( void );
	bool ValidateIndex( void );
};

#endif  // TESTWORKER_H
