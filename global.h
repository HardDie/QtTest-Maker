#ifndef GLOBAL_H
#define GLOBAL_H

#include <QString>

struct Question {
	QString _question;
	QString _answer;
};

enum phase_t {
	PHASE_NOTSET = 0,
	PHASE_FIRST,
	PHASE_SECOND,
	PHASE_NEXTWORD,
};

enum mix_phase_t {
	MIX_PHASE_NOTSET = 0,
	MIX_PHASE_FIRST,
	MIX_PHASE_SECOND,
};

enum testmode_t {
	TESTMODE_NOTSET = 0,
	TESTMODE_QA,
	TESTMODE_AQ,
};

enum flagstate_t {
	FLAGSTATE_NOTSET = 0,
	FLAGSTATE_QA,
	FLAGSTATE_AQ,
};

#endif  // GLOBAL_H
