#ifndef GUIWORKER_H
#define GUIWORKER_H

#include <QObject>

#include "testworker.h"

class GUIWorker : public QObject {
	Q_OBJECT
public:
	explicit GUIWorker( QObject *parent = nullptr );

signals:
	void qmlSetTestString( QString text, QString index );
	void qmlSetTypeTestString( QString text, QString index );
	void qmlReturnToMainMenu();
	void qmlShowMessage( QString text, QString detailedText ) const;
	void qmlShowExitMessage( QString text, QString detailedText ) const;
	void qmlAddItemToList( QString _question, QString _answer ) const;
	void qmlExitFromApp() const;

public slots:
	void setTestModeQA();
	void setTestModeAQ();
	void setTestModeMix();

	void setTestModeTypeQA();
	void setTestModeTypeAQ();
	void setTestModeTypeMix();

	void buttonTestNext();
	void buttonTestTypeCheck( QString userAnswer );
	void buttonTestTypeSkip();

	void openFile( QString url );
	void dictionaryFillList() const;
	void dictionaryDeleteItem( int index );
	void dictionaryAddItem( QString question, QString answer );

	void exitFromApp() const;

private:
	QString getQuestionWithMode( void );
	QString getAnswerWithMode( void );

	TestWorker _testWorker;
	phase_t    _phase;
	testmode_t _testmode;
	bool       _randmode;
};

#endif  // GUIWORKER_H
