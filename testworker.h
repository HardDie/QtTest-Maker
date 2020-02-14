#ifndef TESTWORKER_H
#define TESTWORKER_H

#include <QString>
#include <QList>

#include "global.h"

struct TestElement {
	struct Question _question;
	flagstate_t     _flag;
};

class TestWorker {
public:
	TestWorker();
	bool ReadFromFile( const QString &filename );
	void FlushFlags( void );

	QString GetIndexString( bool random = false );
	QString GetQuestion( bool random = false );
	QString GetAnswer( bool random = false );
	bool    Next( bool random = false );
	bool    isDictionaryExist() const;

private:
	QList< struct TestElement > _listData;
	int                         _currentIndex;
	mix_phase_t                 _mix_phase;

	flagstate_t GetRandFlag();
	void        FlushData( void );
	void        Shuffle( void );
};

#endif  // TESTWORKER_H
